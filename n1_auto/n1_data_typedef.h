#ifndef N1_DATA_TYPEDEF_H
#define N1_DATA_TYPEDEF_H


#pragma pack(1)

typedef unsigned char u8_t;
typedef unsigned short u16_t;
typedef unsigned int u32_t;

//
// 数据结构和类型定义.
//--------------------------------------------------
typedef struct _SIMPLE_MESSAGE_PHR_t //简易消息头
{
  u8_t ucMagic;
       #define    SNCMAGIC         0xCAu
       #define    SNNMAGIC         0xFEu
         #define    SN1MAGIC				 0xCCu
             #define		EXT_MAGIC        0XCBu
  u8_t ucMsgType;
    //----------------------SN1--add  new type by suojf  2013.05.09
             #define    SN1_N1SYNC_NO          0x01u
             #define    SN1_RSSI_RSP_NO  			 0x80u
             #define    SN1_N1DotTable_REQ_NO  0x81u
             #define    SN1_N1DotTable_RSP_NO  0x82u
             #define    SN1_N1SysTable_RSP_NO  0x83u
  //----------------------SNC
       #define    CONNECTREQ              0x01u
       #define    CONNECTRSP              0x02u
       #define    DISCONNECTREQ           0x03u
  //------------------------SNN
       #define    SNN_STATUS_RSP_NO             0x01u
       #define    SNN_CONFIGURE_REQ_NO          0x02u
       #define    SNN_CONFIGURE_RSP_NO          0x03u
       #define    SNN_DATA_MSG_NO               0x04u
       #define    SNN_DATA_REQ_NO               0x0Au
       #define    SNN_DATA_RSP_NO               0x0Bu
       #define    SNN_DOT_COMMAND_REQ_NO        0x0Cu
       #define    SNN_DOT_COMMAND_RSP_NO        0x0Du
       #define    SNN_SAVE_REQ_NO               0x12u
       #define    SNN_SAVE_RSP_NO               0x13u
       #define    SNN_REBOOT_REQ_NO             0x14u
       #define    SNN_REBOOT_RSP_NO             0x15u
       #define    SNN_GO_REQ_NO                 0x16u
       #define    SNN_GO_RSP_NO                 0x17u
       #define    SNN_ALIVE_REQ_NO              0x18
       #define    SNN_ALIVE_RSP_NO              0x19u
       #define    SNN_SEND_REQ_NO               0x1Au
       #define    SNN_SEND_RSP_NO               0x1Bu
       #define    SNN_TABLE_OP_REQ_NO           0x1Cu
       #define    SNN_TABLE_OP_RSP_NO           0x1Du
       #define    SNN_TABLE_OP_MSG_NO           0x1E
       #define    SNN_TABLE_MODIFIED_MSG_NO     0x1Fu
       #define    SNN_MASTER170_CH_MSG_NO       0x20u
       #define    SNN_MASTER170_CH_RSP_NO       0x21u
       #define    SNN_MASTER170_CARD_MSG_NO     0x22u
       #define    SNN_MASTER170_CARD_RSP_NO     0x23u
       #define    SNN_DOT_SETID_COMMAND_REQ_NO  0x24u
       #define    SNN_DOT_SETID_COMMAND_RSP_NO  0x25u

             #define 		EXT_AP_PARAM									 0X01U
             #define 		EXT_AP_ID_VERSION							 0X02U
             #define 		EXT_AP_SET_SENSOR							 0X03U
           #define    EXT_AP_UPDATA                  0x04U
           #define    EXT_AP_BACKUP                  0x05U
           #define    EXT_AP_GET_BACKUP              0x06U
             #define    EXT_AP_DTU_DATA		             0x07U

  u8_t ucLength;
 }SIMPLE_MESSAGE_PHR_t;


typedef struct _BASE_MESSAGE_PHR_t//基本消息头
{
  SIMPLE_MESSAGE_PHR_t    sPhr;
  u8_t                    ucTarget;
  u8_t                    ucSource;
              #define   SOURCEID 0xFF
  u8_t                    ucSeq;
  u8_t                    ucVersion;
              #define   VERSION 0x01u
  u8_t                    ucReserve;

}BASE_MESSAGE_PHR_t;

//----------------------------------------------

typedef struct _SNNDATA_MESSAGE//SNNDATA消息
{
  BASE_MESSAGE_PHR_t      basePhr;
  u32_t                   lTimestamp;
  u16_t                   sTime;
  u8_t                    ucLqi;
  u8_t                    ucRssi;
  u8_t                    ucOffset;
  u8_t                    ucLoadData[0x40];
}SNNDATA_MESSAGE;





// SNP协议包头结构.
typedef struct _SNP_PHR_t
{
    u8_t		ucSize;			// sizeof(MPDU) or sizeof(Packet). 1B
    u16_t		uiFcf;			// FCF 8000
                     #define FCFL_FRAMETYPE_BEACON 0x00u
                     #define FCFL_FRAMETYPE_DATA   0x01u
                     #define FCFL_INTRAPAN         0x40u
                     #define FCFH_SRC_SHORT        0x80u
    u8_t		ucSerNr;		// SN
    u16_t		uiDevId;		// Device(Sensor or Repeater) ID.
        #define SNP_DEVICE_ID_AP			0xFFF0u		// AP(Access Point) ID.
    u16_t		uiType;			// 类型(Packet type).
        #define	SNP_PACKET_TYPE_SYNC		( 1u )		// 同步.
        #define	SNP_PACKET_TYPE_STATE		( 2u )		// 状态(事件)报告.
        #define	SNP_PACKET_TYPE_SEN_CFG		( 3u )		// SEN(Sensor)配置.
        #define	SNP_PACKET_TYPE_RP_CFG		( 5u )		// RP(Repeater)配置.
        #define	SNP_PACKET_TYPE_UF_CFG		( 7u )		// 更新固件配置.
        #define SNP_PACKET_TYPE_SEN_A		SNP_SENSOR_MODE_A
        #define SNP_PACKET_TYPE_SEN_B		SNP_SENSOR_MODE_B
        #define SNP_PACKET_TYPE_SEN_D		SNP_SENSOR_MODE_D
        #define SNP_PACKET_TYPE_SEN_E		SNP_SENSOR_MODE_E
        #define SNP_PACKET_TYPE_SEN_F		SNP_SENSOR_MODE_F
        #define SNP_PACKET_TYPE_SEN_G		SNP_SENSOR_MODE_G
        #define	SNP_PACKET_TYPE_AP_ACK		( 0x6Eu )	// AP(Access Point)应答.
        #define	SNP_PACKET_TYPE_RP_ACK		( 0xC8u )	// RP(Repeater)应答.
        #define SNP_PACKET_TYPE_UF_DATA		( 0xD2u )	// 更新固件的数据.
        #define	SNP_PACKET_TYPE_UF_ACK		( 0xD3u )	// 更新固件应答.
    // v4.0新增两个无线数据包类型 2011-11-15
        #define SNP_PACKET_TYPE_SEN_C		SNP_SENSOR_MODE_C
        #define SNP_PACKET_TYPE_SEN_H		SNP_SENSOR_MODE_H
} SNP_PHR_t;

// SNP协议同步包结构.26个字节
typedef struct _SNP_SYNC_PACKET_t
{
    SNP_PHR_t	sPhr;

    u8_t		ucCurSecNr;		// 0x8	-	主机当前时刻(秒) mod 'ucSecPeriod'  10
    u8_t		ucSecPeriod;	// 0x9	-	循环周期(秒)  1E=30
    u8_t		ucSlotLength;	// 0xA	-	时隙长度, 单位: 1 / 32.768KHz.  40
    u8_t		ucCtrlBm;		// 0xB	-	  46
        #define SNP_CTRL_BM_NSEC			( 1u<<0u )	// BIT.0 = 0:	在'秒'边界.
        #define SNP_CTRL_BM_BIT1			( 1u<<1u )	// BIT.1 = 1:	???  UNMANAGED
        #define SNP_CTRL_BM_REQ_ACK			( 1u<<2u )	// BIT.2 = 1:	检测器期望AP应答,
                                                        //				参考'Page 170: Enabling Expectation of Acknowledgments'.
        #define SNP_CTRL_BM_FAST_CAL		( 1u<<3u )	// BIT.3 = 1:	始终使用快速校准同步误差.
                                                        //		 = 0:	允许使用较慢校准同步误差.
        #define SNP_CTRL_BM_BIT4			( 1u<<4u )	// BIT.4 = 1:	允许大的同步误差.
        #define SNP_CTRL_BM_TANDEM			( 1u<<5u )	// BIT.5 = 1:	有串联(Tandem)的Repeater.
                                                        //		 = 0:	没有串联(Tandem)的Repeater.
        #define SNP_CTRL_BM_ACK				( 1u<<6u )	// BIT.6 = 1:使用g_sStatePacket作为应答.
                                        //= 0:	使用g_sRpAckPacket或g_sUfAckPacket作为应答.
    union{
        u16_t	uiRemainSlot;	// 0xC	-	不在'秒'边界时的同步包用, 解析为: 当前'秒'周期内剩余的时隙数.
        u16_t	uiPathInfo;	// 0xC	-	在'秒'边界时的同步包用, 解析为:
                                //低字节为从主机发出同步/数据包到收到下端设备的应答包所额外增加的时隙数,
                                //高字节为从主机发出同步/数据包到下端设备收到这个包所间隔的时隙数.

     }Second_Edge;
    u16_t		uiChangeCnt;	// 0xE	-	本机与AP之间的设备的无线参数更改计数, 用于校验后续同步包的无线路径或无线参数的一致性.
    u16_t		uiDestId;		// 0x10	-	与本机ID匹配时, 执行'uiCmd'定义的命令.
    u16_t		uiCmd;			// 0x12	-	低四位定义命令类型, 其余位右移四位作为命令参数.
        #define SNP_CMD_TOTAL				( 16u )
        #define SNP_CMD_bm					( SNP_CMD_TOTAL - 1u )
        #define SNP_CMD_PARM_bp				( 4u )
        #define SNP_CMD_PARM_bm				( ~SNP_CMD_bm )
        #define SNP_CMD_LED_CTRL			( 1u )		//
        #define SNP_CMD_SEN_RECAL			( 2u )		//
        #define SNP_CMD_SEN_SET_MODE		( 3u )		//
        #define SNP_CMD_EXIT_UF				( 4u )		//
        #define SNP_CMD_SET_SLOT			( 5u )		//
        #define SNP_CMD_CHANGE_CFG			( 6u )		//
        #define SNP_CMD_ENTER_UF			( 7u )		//
        #define SNP_CMD_SEN_SET_MISC		( 8u )		//
  u8_t SystemParameter[6];         //时间槽分档为第1和第6个字节
} SNP_SYNC_PACKET_t;

// SNP协议状态(事件)包结构.
typedef struct _SNP_STATE_PACKET_t
{
    SNP_PHR_t	sPhr;//同步头

    u16_t		uiFwVer;			// 0x8	-	当前固件版本. 0x0035
    u16_t		uiHwVer;			// 0xA	-	本机硬件版本.
    u8_t		ucCfgComb;			// 0xC	-	??? configuration combination.
                                    //			定义本机可实现的功能:
                                    //			0x03:	检测器.
                                    //			0x07:	中继器.
                                    //			0x08:	检测器仅'Stop Bar'模式.
    u8_t		ucVolt;				// 0xD	-	本机的电源电压测量值: ADC / 16.
    u16_t		uiChannel;			// 0xE	-	本机无线通道, 'Bit Map'结构:
                                    //			Bit.0-Bit.3: 与父节点通讯的RF通道.
                                    //			Bit.4-Bit.7: 与子节点通讯的RF通道, 如果需要.
                                    //			Bit.8:		???
                                    //			Bit.9:		中继器时隙配置.
    u16_t		uiRpId;				// 0x10	-	中继器的'RF-ID'.
    u16_t		uiSubType;			// 0x12	-	代替包类型.
    u16_t		uiSubData;			// 0x14	-	代替包数据, 成功编程FLASH的次数.
    int	        ulFactoryId;
    u16_t       uiBindId;
} SNP_STATE_PACKET_t;



#pragma pack()



#define RP_MUX_NUM 24
#define Sensor_MUX_NUM 64

struct _n1_device_list{
    int ap_channel_cfg;
    int ap_channel;
    int rp_num_cfg;
    int sensor_num_cfg;
    int rp_num_rcv;
    int sensor_num_rcv;
    struct _rp{
        unsigned int rp_id;
        unsigned int uiBindId;
        int level;            //rp 处于那一级，（直连到ap 算是1级）
        int up_channel;
        int down_channel;
        int up_channel_cfg;
        int down_channel_cfg;
        unsigned int father_id_cfg;
        unsigned int father_id;
        int set_slot;
        int slot;
        int rp_type_cfg;
        int rp_type;
        int sec_dot;
        int timeout;
        int adjust_fail;  //调整失败了
        int rssi;
        int own_sensor_num[2];  //所带的sensor数量 0是下级 1是下下级
    }rp[RP_MUX_NUM];
    struct _sensor{
        unsigned int sensor_id;
        int level;            //sensor 处于那一级，（直连到ap 算是1级）
        unsigned int uiBindId;
        int channel_cfg;
        int channel;
        unsigned int father_id;
        unsigned int father_id_cfg;
        int set_slot;
        int slot;
        int sec_dot;
        int timeout;
        int adjust_fail;  //调整失败了
        int rssi;
    }sensor[Sensor_MUX_NUM];
};





// 事件信息.
#pragma anon_unions
typedef union _SNP_EVENT_t
{
    u16_t		uiAll;
    struct{
    u16_t	bmMs:   10,	// 毫秒数, 'SNP_REF_TIME_US'的32倍: 0.9765625ms.
        bmSec:  5,	// 秒数.
        blIsOn: 1;	// 事件'ON'/'OFF', 'ON' = 1.
  };
} SNP_EVENT_t;
#pragma no_anon_unions


// Mode = B: Vehicle count stations
// 模式'Count'和'Stop Bar'公用数据包.
typedef struct _SNP_SEN_MODE_B_PACKET_t
{
    SNP_PHR_t	sPhr;
    //u8_t        uAdress170;
    SNP_EVENT_t	asEvent[16u];	// 0x08 -事件信息队列.
} SNP_SEN_MODE_B_PACKET_t;






#endif // N1_DATA_TYPEDEF_H
