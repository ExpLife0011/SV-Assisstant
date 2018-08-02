#pragma once
#pragma warning(disable:4035)
#include <windows.h>
#include <winioctl.h>
#include <atacct.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <Ntddscsi.h>
#include "WMI for Disk/SynQuery.h"
/**
��Ϣ��Դ��
https://www.cnblogs.com/huhu0013/p/4283436.html
*/
// IOCTL������
#define DFP_SEND_DRIVE_COMMAND					0x0007C084
//#define DFP_SEND_DRIVE_COMMAND CTL_CODE(IOCTL_DISK_BASE, 0x0021, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define DFP_RECEIVE_DRIVE_DATA					0x0007C088
//#define DFP_RECEIVE_DRIVE_DATA CTL_CODE(IOCTL_DISK_BASE, 0x0022, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)

//From DDK

#define	FILE_DEVICE_SCSI							0x0000001b
#define	IOCTL_SCSI_MINIPORT_IDENTIFY				((FILE_DEVICE_SCSI << 16) + 0x0501)
#define	IOCTL_SCSI_MINIPORT_READ_SMART_ATTRIBS		((FILE_DEVICE_SCSI << 16) + 0x0502)
#define IOCTL_SCSI_MINIPORT_READ_SMART_THRESHOLDS	((FILE_DEVICE_SCSI << 16) + 0x0503)
#define IOCTL_SCSI_MINIPORT_ENABLE_SMART			((FILE_DEVICE_SCSI << 16) + 0x0504)
#define IOCTL_SCSI_MINIPORT_DISABLE_SMART			((FILE_DEVICE_SCSI << 16) + 0x0505)

//
// Valid values for the bCommandReg member of IDEREGS.
//

#define ATAPI_ID_CMD			  0xA1            // Returns ID sector for ATAPI.
#define IDE_ATA_IDENTIFY          0xEC            // Returns ID sector for ATA.
#define SMART_CMD				  0xB0            // Performs SMART cmd.
// Requires valid bFeaturesReg,
// bCylLowReg, and bCylHighReg

//
// Cylinder register defines for SMART command
//

#define SMART_CYL_LOW   0x4F
#define SMART_CYL_HI    0xC2

#define	MAX_ATTRIBUTE	30

typedef enum _TRANSFER_MODE
{
	TRANSFER_MODE_UNKNOWN = 0,
	TRANSFER_MODE_PIO,
	TRANSFER_MODE_PIO_DMA,
	TRANSFER_MODE_ULTRA_DMA_16,
	TRANSFER_MODE_ULTRA_DMA_25,
	TRANSFER_MODE_ULTRA_DMA_33,
	TRANSFER_MODE_ULTRA_DMA_44,
	TRANSFER_MODE_ULTRA_DMA_66,
	TRANSFER_MODE_ULTRA_DMA_100,
	TRANSFER_MODE_ULTRA_DMA_133,
	TRANSFER_MODE_SATA_150,
	TRANSFER_MODE_SATA_300,
	TRANSFER_MODE_SATA_600
}TRANSFER_MODE;

typedef enum _HOST_READS_WRITES_UNIT
{
	HOST_READS_WRITES_UNKNOWN = 0,
	HOST_READS_WRITES_512B,
	HOST_READS_WRITES_32MB,
	HOST_READS_WRITES_GB,
}HOST_READS_WRITES_UNIT;

typedef	enum _VENDOR_ID
{
	HDD_GENERAL = 0,
	SSD_GENERAL = 1,
	SSD_VENDOR_MTRON = 2,
	SSD_VENDOR_INDILINX = 3,
	SSD_VENDOR_JMICRON = 4,
	SSD_VENDOR_INTEL = 5,
	SSD_VENDOR_SAMSUNG = 6,
	SSD_VENDOR_SANDFORCE = 7,
	SSD_VENDOR_MICRON = 8,
	SSD_VENDOR_OCZ = 9,
	HDD_SSD_VENDOR_SEAGATE = 10,
	HDD_VENDOR_WESTERN_DIGITAL = 11,
	SSD_VENDOR_PLEXTOR = 12,
	SSD_VENDOR_SANDISK = 13,
	SSD_VENDOR_OCZ_VECTOR = 14,
	HDD_SSD_VENDOR_TOSHIBA = 15,
	SSD_VENDOR_CORSAIR = 16,
	SSD_VENDOR_KINGSTON = 17,
	SSD_VENDOR_MICRON_MU02 = 18,
	SSD_VENDOR_NVME = 19,
	SSD_VENDOR_MAX = 99,

	VENDOR_UNKNOWN = 0x0000,
	USB_VENDOR_BUFFALO = 0x0411,
	USB_VENDOR_IO_DATA = 0x04BB,
	USB_VENDOR_LOGITEC = 0x0789,
	USB_VENDOR_INITIO = 0x13FD,
	USB_VENDOR_SUNPLUS = 0x04FC,
	USB_VENDOR_JMICRON = 0x152D,
	USB_VENDOR_CYPRESS = 0x04B4,
	USB_VENDOR_OXFORD = 0x0928,
	USB_VENDOR_PROLIFIC = 0x067B,
	USB_VENDOR_ALL = 0xFFFF,
}VENDOR_ID;

typedef	enum _POWER_ON_HOURS_UNIT
{
	POWER_ON_UNKNOWN = 0,
	POWER_ON_HOURS,
	POWER_ON_MINUTES,
	POWER_ON_HALF_MINUTES,
	POWER_ON_SECONDS,
	POWER_ON_10_MINUTES,
	POWER_ON_MILLI_SECONDS,
}POWER_ON_HOURS_UNIT;

static const TCHAR *ssdVendorString[] =
{
	_T(""),
	_T(""),
	_T("mt"), // MTron
	_T("ix"), // Indilinx
	_T("jm"), // JMicron
	_T("il"), // Intel
	_T("sg"), // SAMSUNG
	_T("sf"), // SandForce
	_T("mi"), // Micron
	_T("oz"), // OCZ
	_T("st"), // SEAGATE
	_T("wd"), // WDC
	_T("px"), // PLEXTOR
	_T("sd"), // SanDisk
	_T("oz"), // OCZ Vector
	_T("to"), // TOSHIABA
	_T("co"), // Corsair
	_T("ki"), // Kingston
	_T("m2"), // Micron MU02
	_T("nv"), // NVMe
};

static const TCHAR *deviceFormFactorString[] =
{
	_T(""),
	_T("5.25 inch"),
	_T("3.5 inch"),
	_T("2.5 inch"),
	_T("1.8 inch"),
	_T("< 1.8 inch")
};

// IDE��ID����ص�����
// ��512�ֽ� (256��WORD)�������������һЩ����Ȥ����(����������ATA/ATAPI-4)
#pragma pack(push,1)
struct IDINFO
{
	USHORT wGenConfig; // WORD 0: ������Ϣ��
	USHORT wNumCyls; // WORD 1: ������
	USHORT wReserved2; // WORD 2: ����
	USHORT wNumHeads; // WORD 3: ��ͷ����
	USHORT wReserved4; // WORD 4: ����
	USHORT wReserved5; // WORD 5: ����
	USHORT wNumSectorsPerTrack;// WORD 6: ÿ�� ��������
	USHORT wVendorUnique[3]; // WORD 7-9: �����趨ֵ
	CHAR sSerialNumber[20]; // WORD 10-19:���к�
	USHORT wBufferType;// WORD 20: ������ ��
	USHORT wBufferSize;// WORD 21: �����С
	USHORT wECCSize; // WORD 22: ECCУ���С
	CHAR sFirmwareRev[8]; // WORD 23-26: �̼��汾
	CHAR sModelNumber[40]; // WORD 27-46: �ڲ��ͺ�
	USHORT wMoreVendorUnique; // WORD 47: �����趨ֵ
	USHORT wReserved48;// WORD 48: ����
	union 
	{
		struct {
			USHORT reserved1 : 8;
			USHORT DMA : 1; // 1=֧��DMA
			USHORT LBA : 1; // 1=֧�� LBA
			USHORT DisIORDY : 1;// 1=�ɲ�ʹ��IORDY
			USHORT IORDY : 1;// 1=֧�� IORDY
			USHORT SoftReset : 1; // 1=��ҪATA������
			USHORT Overlap : 1;// 1= ֧���ص�����
			USHORT Queue : 1;// 1=֧���������
			USHORT InlDMA : 1;// 1=֧�ֽ����ȡDMA
		}bits;
		USHORT Capabilities;
	}wCapabilities; // WORD 49: һ������
	USHORT wReserved1;  // WORD 50: ����
	USHORT wPIOTiming; // WORD 51: PIOʱ��
	USHORT wDMATiming; // WORD 52: DMAʱ��
	union 
	{
		struct {
			USHORT CHSNumber : 1; // 1=WORD 54-58��Ч
			USHORT CycleNumber : 1; // 1=WORD 64-70��Ч
			USHORT UnltraDMA : 1;  // 1=WORD 88��Ч
			USHORT reserved : 13;
		}bits;
		USHORT FieldValidity;
	}wFieldValidity; // WORD 53: �� ���ֶ���Ч�Ա�־
	USHORT wNumCurCyls;// WORD 54: CHS��Ѱַ��������
	USHORT wNumCurHeads;// WORD 55: CHS��Ѱַ�Ĵ�ͷ��
	USHORT wNumCurSectorsPerTrack; // WORD 56: CHS��Ѱַÿ�ŵ�������
	USHORT wCurSectorsLow;// WORD 57: CHS��Ѱַ������ ����λ��
	USHORT wCurSectorsHigh; // WORD 58: CHS��Ѱַ����������λ��
	union 
	{
		struct {
			USHORT CurNumber : 8; // ��ǰһ���Կɶ�д������
			USHORT Multi : 1;// 1=��ѡ���������д
			USHORT reserved1 : 7;
		}bits;
		USHORT MultSectorStuff;
	}wMultSectorStuff; // WORD 59: �� ������д�趨
	ULONG dwTotalSectors;// WORD 60-61: LBA��Ѱַ��������
	USHORT wSingleWordDMA;// WORD 62: ���ֽ�DMA֧��������
	union 
	{
		struct {
			USHORT Mode0 : 1;// 1=֧��ģʽ0 (4.17Mb/s)
			USHORT Mode1 : 1;// 1=֧��ģʽ1 (13.3Mb/s)
			USHORT  Mode2 : 1;// 1=֧��ģʽ2 (16.7Mb/s)
			USHORT Reserved1 : 5;
			USHORT Mode0Sel : 1;// 1=��ѡ��ģʽ0
			USHORT Mode1Sel : 1;// 1=��ѡ��ģʽ1
			USHORT Mode2Sel : 1;// 1=��ѡ��ģʽ2
			USHORT Reserved2 : 5;
		}bits;
		USHORT MultiWordDMA;
	}wMultiWordDMA; // WORD 63: ���ֽ�DMA֧������
	struct {
		USHORT AdvPOIModes : 8; // ֧�ָ� ��POIģʽ��
		USHORT reserved : 8;
	} wPIOCapacity; // WORD 64: �߼�PIO֧���� ��
	USHORT wMinMultiWordDMACycle; // WORD 65: ���ֽ�DMA�������ڵ���Сֵ
	USHORT  wRecMultiWordDMACycle; // WORD 66: ���ֽ�DMA�������ڵĽ���ֵ
	USHORT wMinPIONoFlowCycle; // WORD 67: ��������ʱPIO�������ڵ���Сֵ
	USHORT wMinPOIFlowCycle; // WORD 68: ��������ʱPIO�������ڵ���Сֵ
	USHORT wReserved69[11]; // WORD 69-79: ����
	union 
	{
		struct {
			USHORT Reserved1 : 1;
			USHORT ATA1 : 1; // 1=֧��ATA-1
			USHORT ATA2 : 1; // 1=֧��ATA-2
			USHORT ATA3 : 1; // 1=֧��ATA-3
			USHORT ATA4 : 1; // 1=֧��ATA/ATAPI-4
			USHORT ATA5 : 1; // 1=֧��ATA/ATAPI-5
			USHORT ATA6 : 1; // 1=֧��ATA/ATAPI-6
			USHORT ATA7 : 1; // 1=֧��ATA/ATAPI-7
			USHORT ATA8 : 1; // 1=֧��ATA/ATAPI- 8
			USHORT ATA9 : 1; // 1=֧��ATA/ATAPI-9
			USHORT ATA10 : 1; // 1=֧�� ATA/ATAPI-10
			USHORT ATA11 : 1; // 1=֧��ATA/ATAPI-11
			USHORT ATA12 : 1; // 1=֧��ATA/ATAPI-12
			USHORT ATA13 : 1;// 1=֧��ATA/ATAPI-13
			USHORT ATA14 : 1;// 1=֧��ATA/ATAPI-14
			USHORT Reserved2 : 1;
		}bits;
		USHORT MajorVersion;
	}wMajorVersion; // WORD 80: ���汾
	USHORT wMinorVersion;// WORD 81: ���汾
	USHORT wReserved82[6];// WORD 82-87: ����
	union 
	{
		struct {
			USHORT Mode0 : 1;// 1=֧�� ģʽ0 (16.7Mb/s)
			USHORT Mode1 : 1;// 1=֧��ģʽ1 (25Mb/s)
			USHORT Mode2 : 1;// 1=֧��ģʽ2 (33Mb/s)
			USHORT Mode3 : 1;// 1=֧��ģʽ3 (44Mb/s) USHORT Mode4:1;// 1=֧��ģʽ4 (66Mb/s)
			USHORT Mode5 : 1;// 1=֧��ģʽ5 (100Mb/s)
			USHORT Mode6 : 1;// 1=֧��ģʽ6 (133Mb/s)
			USHORT Mode7 : 1; // 1=֧��ģʽ7 (166Mb/s) ???
			USHORT Mode0Sel : 1;// 1=��ѡ��ģʽ0
			USHORT  Mode1Sel : 1;// 1=��ѡ��ģʽ1
			USHORT Mode2Sel : 1;// 1=��ѡ��ģʽ2
			USHORT Mode3Sel : 1;// 1=��ѡ��ģʽ3
			USHORT Mode4Sel : 1;// 1=��ѡ��ģʽ4
			USHORT Mode5Sel : 1;// 1=��ѡ��ģʽ5
			USHORT Mode6Sel : 1;// 1=��ѡ��ģʽ 6
			USHORT Mode7Sel : 1;// 1=��ѡ��ģʽ7
		}bits;
		USHORT UltraDMA;
	}wUltraDMA; // WORD 88: Ultra DMA֧������;
	USHORT wReserved89[167]; // WORD 89-255
};

typedef IDINFO *PIDINFO;

struct SMART_THRESHOLD
{
	BYTE	Id;
	BYTE	ThresholdValue;
	BYTE	Reserved[10];
};

struct SMART_ATTRIBUTE
{
	BYTE	Id;
	WORD	StatusFlags;
	BYTE	CurrentValue;
	BYTE	WorstValue;
	BYTE	RawValue[6];
	BYTE	Reserved;
};

//��Ҫ����ע�����IDINFO��57 - 58 WORD(CHS��Ѱַ��������)����Ϊ������32λ�����Ҫ�󣬲��ɶ���Ϊһ��ULONG�ֶΡ�Lynn McGuire�ĳ������������ڶ���Ϊһ��ULONG�ֶΣ����¸ýṹ�����á�
#pragma pack(pop)
// SCSI�������������������õĽṹ
/*typedef struct _SRB_IO_CONTROL
{
	ULONG HeaderLength; // ͷ����
	UCHAR Signature[8]; // ��������
	ULONG Timeout; // ��ʱʱ��
	ULONG ControlCode; // ������
	ULONG ReturnCode; // ������
	ULONG Length; // ����������
} SRB_IO_CONTROL, *PSRB_IO_CONTROL;
// IDE���� �Ĵ���
typedef struct _IDEREGS
{
BYTE bFeaturesReg;// �����Ĵ��� (����SMART ����)�� BYTE bSectorCountReg;�� // ������Ŀ�Ĵ���
BYTE bSectorNumberReg;// ��ʼ�����Ĵ���
BYTE bCylLowReg; // ��ʼ������ֽ� �Ĵ���
BYTE bCylHighReg; // ��ʼ������ֽڼĴ���
BYTE bDriveHeadReg; // ������/��ͷ�Ĵ���
BYTE bCommandReg; // ָ��Ĵ���
BYTE bReserved; // ����
} IDEREGS, *PIDEREGS, *LPIDEREGS;
// ���������򷵻ص�״̬
typedef struct _DRIVERSTATUS
{
BYTE bDriverError;  // ������
BYTE bIDEStatus; // IDE״̬�Ĵ���
BYTE bReserved[2]; // ����
DWORD dwReserved[2]; // ����
} DRIVERSTATUS, *PDRIVERSTATUS, *LPDRIVERSTATUS;
// IDE�豸IOCTL�������ݽṹ
typedef struct _SENDCMDINPARAMS
{
DWORD cBufferSize;// �������ֽ���
IDEREGS irDriveRegs;// IDE�Ĵ�����
BYTE bDriveNumber;// ��������
BYTE bReserved[3];//����
DWORD dwReserved[4]; //����
BYTE bBuffer[1]; //���뻺����(�˴������Եذ���1�ֽ�)
} SENDCMDINPARAMS, *PSENDCMDINPARAMS, *LPSENDCMDINPARAMS;
// IDE�豸IOCTL������ݽṹ
typedef struct _SENDCMDOUTPARAMS
{
DWORD cBufferSize;// ������ �ֽ���
DRIVERSTATUS DriverStatus; // �������򷵻�״̬
BYTE bBuffer[1]; // ���뻺����(�˴������Եذ���1�ֽ�)
} SENDCMDOUTPARAMS, *PSENDCMDOUTPARAMS, *LPSENDCMDOUTPARAMS;*/

struct SMART_READ_DATA_OUTDATA
{
	SENDCMDOUTPARAMS	SendCmdOutParam;
	BYTE				Data[READ_ATTRIBUTE_BUFFER_SIZE - 1];
};

struct ATA_SMART_INFO
{
	ATA_SMART_INFO();
	IDINFO				Identify;
	BYTE				SmartReadData[512];
	BYTE				SmartReadThreshold[512];
	SMART_ATTRIBUTE		Attribute[MAX_ATTRIBUTE];
	SMART_THRESHOLD		Threshold[MAX_ATTRIBUTE];
	wstring				model;
	wstring				deviceid;
	wstring				diskSize;
	wstring				mediaType;
	wstring				interfaceTypeWmi;
	wstring				pnpDeviceId;
	wstring				firmware;
	wstring				MajorVersion;
	wstring				MinorVersion;
	wstring				MaxTransferMode;
	wstring				CurrentTransferMode;
	wstring				Interface;
	wstring				SmartKeyName;
	wstring				SsdVendorString;
	INT					physicalDriveId;
	INT					scsiPort;
	INT					scsiTargetId;
	INT					scsiBus;
	DWORD				AttributeCount;
	DWORD				DiskVendorId;
	DWORD				Major;
	INT					HostWrites;
	INT					HostReads;
	INT					GBytesErased;
	INT					NandWrites;
	INT					WearLevelingCount;
	INT					Life;
	HOST_READS_WRITES_UNIT HostReadsWritesUnit;
	INT					PowerOnRawValue;
	INT					PowerOnStartRawValue;
	DWORD				PowerOnCount;
	INT					Temperature;
	double				TemperatureMultiplier;
	INT					DetectedPowerOnHours;
	INT					MeasuredPowerOnHours;
	DWORD				TransferModeType;
	DWORD				DetectedTimeUnitType;
	DWORD				MeasuredTimeUnitType;
	BOOL				IsSsd;
	BOOL				IsRawValues8;
	BOOL				IsRawValues7;
};

typedef ATA_SMART_INFO *PATA_SMART_INFO;

class UnCopyable
{
protected:
	UnCopyable() {}
	~UnCopyable() {}

private:
	explicit UnCopyable(const UnCopyable& x);
	UnCopyable& operator=(const UnCopyable& x);
};

class Disk : private UnCopyable
{
public:
	Disk();
	~Disk();

	VOID UpdateDate();

	vector<ATA_SMART_INFO> SMARTinfo;

private:
	// ��ȡIDEӲ�̵��豸��Ϣ�������� �㹻Ȩ��
	// nDrive: ��������(0=��һ��Ӳ�̣�1=0=�ڶ���Ӳ�̣�......)
	// pIdInfo: �豸��Ϣ�ṹָ��
	BOOL GetPhysicalDriveInfoInNT(int nDrive, PIDINFO pIdInfo);

	// ��SCSI������ȡIDEӲ�̵��豸��Ϣ������Ȩ����Լ
	// nDrive: ��������(0=Primary Master, 1=Promary Slave, 2=Secondary master, 3=Secondary slave)
	// pIdInfo: �豸��Ϣ�� ��ָ��
	BOOL GetIdeDriveAsScsiInfoInNT(int nDrive, PIDINFO pIdInfo);

	BOOL GetPhysicalSMARTInfo(INT nDrive, BYTE target, ATA_SMART_INFO& SMART_info);
	BOOL GetPhysicalThresholdInfo(INT nDrive, BYTE target, ATA_SMART_INFO& SMART_info);
	BOOL GetScsiSMARTInfo(INT scsiPort, INT scsiTargetId, ATA_SMART_INFO& SMART_info);
	BOOL GetScsiThresholdInfo(INT scsiPort, INT scsiTargetId, ATA_SMART_INFO& SMART_info);

	// ���豸
	// filename: �豸�ġ��ļ�����
	HANDLE OpenDevice(LPCTSTR filename);

	// ����������IDENTIFY DEVICE���������豸��Ϣ
	// hDevice: �豸���
	// pIdInfo:���豸��Ϣ�ṹָ��
	BOOL IdentifyDevice(HANDLE hDevice, PIDINFO pIdInfo);

	// ��SCSI MINI-PORT ��������IDENTIFY DEVICE���������豸��Ϣ
	// hDevice: �豸��� 
	// pIdInfo:���豸��Ϣ�ṹָ��
	BOOL IdentifyDeviceAsScsi(HANDLE hDevice, int nDrive, PIDINFO pIdInfo);

	// �����е��ַ������ߵ�
	// ԭ����ATA/ATAPI�е�WORD����Windows���õ��ֽ�˳���� ��
	// �����������Ѿ����յ�������ȫ��������������������������
	void AdjustString(char* str, int len);
	//��ȡATA�ð汾��
	VOID GetAtaMinorVersion(WORD w81, wstring & minor);
	//��ȡ����ʱ��
	DWORD GetPowerOnHours(DWORD rawValue, DWORD timeUnitType);
	DWORD GetTransferMode(WORD w63, WORD w76, WORD w77, WORD w88, wstring & current, wstring & max, wstring & type);
	//ͨ���ַ��ж�Ӳ�̳��� �� Ӳ������ ssd or ��е
	VOID CheckSsdSupport(ATA_SMART_INFO & asi);
	BOOL IsSsdOld(ATA_SMART_INFO & asi);
	BOOL IsSsdMtron(ATA_SMART_INFO & asi);
	BOOL IsSsdJMicron60x(ATA_SMART_INFO & asi);
	BOOL IsSsdJMicron61x(ATA_SMART_INFO & asi);
	BOOL IsSsdIndlinx(ATA_SMART_INFO & asi);
	BOOL IsSsdIntel(ATA_SMART_INFO & asi);
	BOOL IsSsdSamsung(ATA_SMART_INFO & asi);
	BOOL IsSsdSandForce(ATA_SMART_INFO & asi);
	BOOL IsSsdMicronMU02(ATA_SMART_INFO & asi);
	BOOL IsSsdMicron(ATA_SMART_INFO & asi);
	BOOL IsSsdOcz(ATA_SMART_INFO & asi);
	BOOL IsSsdOczVector(ATA_SMART_INFO & asi);
	BOOL IsSsdPlextor(ATA_SMART_INFO & asi);
	BOOL IsSsdSanDisk(ATA_SMART_INFO & asi);
	BOOL IsSsdKingston(ATA_SMART_INFO & asi);
	BOOL IsSsdToshiba(ATA_SMART_INFO & asi);
	//������SMART�е���Ϣ
	DWORD GetTimeUnitType(wstring Model, wstring Firmware, DWORD major, DWORD transferMode);
	BOOL FillSmartData(ATA_SMART_INFO * asi);
	VOID GetSMARTIDINFO(ATA_SMART_INFO * asi);
	BOOL FillSmartThreshold(ATA_SMART_INFO * asi);
	DWORD GetAtaMajorVersion(WORD w80, wstring & majorVersion);
};

class Diskinfo
{
public:
	static Diskinfo* Instance();
	void updatedisk();
	Diskinfo();
private:
	void ChartoWchar(std::wstring & des, const char * src);
	std::shared_ptr<Disk> m_disk;
	static std::shared_ptr<Diskinfo> m_diskinfo;
}; 