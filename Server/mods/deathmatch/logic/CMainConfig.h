/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/CMainConfig.h
 *  PURPOSE:     XML-based main configuration file parser class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

class CMainConfig;

#pragma once

#include "CCommon.h"
#include "CLogger.h"
#include "CConsole.h"
#include "CXMLConfig.h"
#include <list>

#define MAX_MAP_NAME_LENGTH 64
class CMainConfig;

typedef void (CMainConfig::*PFN_SettingChangeCallback)();

struct SIntSetting
{
    bool                      bSettable;
    bool                      bSavable;
    int                       iMin;
    int                       iDefault;
    int                       iMax;
    const char*               szName;
    int*                      pVariable;
    PFN_SettingChangeCallback changeCallback;
};

class CMainConfig : public CXMLConfig
{
public:
    CMainConfig(CConsole* pConsole, class CLuaManager* pLuaMain);

    bool Load();
    bool LoadExtended();
    bool Save();

    const std::string& GetServerName() { return m_strServerName; };
    SString            GetServerIP();
    SString            GetServerIPList();
    unsigned short     GetServerPort();
    unsigned int       GetMaxPlayers();
    unsigned int       GetHardMaxPlayers();
    void               SetSoftMaxPlayers(unsigned int v) { m_uiSoftMaxPlayers = v; }
    bool               IsHTTPEnabled() { return m_bHTTPEnabled; };

    bool               IsValidPassword(const char* szPassword);
    bool               HasPassword() { return !m_strPassword.empty(); };
    const std::string& GetPassword() { return m_strPassword; };
    bool               SetPassword(const char* szPassword, bool bSave);

    bool         IsVoiceEnabled();
    unsigned int GetVoiceSampleRate() { return m_uiVoiceSampleRate; };
    unsigned int GetVoiceQuality() { return m_ucVoiceQuality; };
    unsigned int GetVoiceBitrate() { return m_uiVoiceBitrate; };

    bool                        GetAseInternetPushEnabled() { return m_iAseMode == 2 && !IsFakeLagCommandEnabled(); }
    bool                        GetAseInternetListenEnabled() { return m_iAseMode == 1 && !IsFakeLagCommandEnabled(); }
    bool                        GetAseLanListenEnabled() { return m_bDontBroadcastLan ? false : true; }
    unsigned short              GetHTTPPort();
    eHTTPDownloadType           GetHTTPDownloadType() { return m_ucHTTPDownloadType; };
    const std::string&          GetHTTPDownloadURL() { return m_strHTTPDownloadURL; };
    int                         GetHTTPMaxConnectionsPerClient() { return m_iHTTPMaxConnectionsPerClient; };
    int                         GetHTTPThreadCount() { return m_iHTTPThreadCount; };
    int                         GetHTTPDosThreshold() { return m_iHTTPDosThreshold; };
    const SString&              GetHTTPDosExclude() { return m_strHTTPDosExclude; };
    int                         GetEnableClientChecks() { return m_iEnableClientChecks; };
    const std::string&          GetLogFile() { return m_strLogFile; };
    const std::string&          GetAuthFile() { return m_strAuthFile; };
    bool                        GetJoinFloodProtectionEnabled() { return m_bJoinFloodProtectionEnabled; };
    bool                        GetScriptDebugLogEnabled() { return m_bScriptDebugLogEnabled && !m_strScriptDebugLogFile.empty(); };
    const std::string&          GetScriptDebugLogFile() { return m_strScriptDebugLogFile; };
    unsigned int                GetScriptDebugLogLevel() { return m_uiScriptDebugLogLevel; };
    const std::string&          GetAccessControlListFile() { return m_strAccessControlListFile; };
    bool                        GetSerialVerificationEnabled() { return m_bVerifySerials; };
    bool                        IsDisableAC(const char* szTagAC) { return MapContains(m_DisableComboACMap, szTagAC); };
    bool                        IsEnableDiagnostic(const char* szTag) { return MapContains(m_EnableDiagnosticMap, szTag); };
    SString                     GetMinClientVersion() { return m_strMinClientVersion; }
    const SString&              GetRecommendedClientVersion() { return m_strRecommendedClientVersion; }
    int                         GetMinClientVersionAutoUpdate() { return m_iMinClientVersionAutoUpdate; }
    const SString&              GetIdFile() { return m_strIdFile; }
    bool                        GetThreadNetEnabled() { return m_bThreadNetEnabled; }
    const SString&              GetGlobalDatabasesPath() { return m_strGlobalDatabasesPath; }
    const SString&              GetSystemDatabasesPath() { return m_strSystemDatabasesPath; }
    const SString&              GetBackupPath() { return m_strBackupPath; }
    int                         GetBackupInterval() { return m_iBackupInterval; }
    int                         GetBackupAmount() { return m_iBackupAmount; }
    void                        NotifyDidBackup();
    bool                        ShouldCompactInternalDatabases();
    unsigned short              GetFPSLimit() { return m_usFPSLimit; };
    bool                        SetFPSLimit(unsigned short usFPS, bool bSave);
    int                         GetPendingWorkToDoSleepTime();
    int                         GetNoWorkToDoSleepTime();
    int                         GetServerLogicFpsLimit() { return m_iServerLogicFpsLimit; };
    const SString&              GetDbLogFilename() { return m_strDbLogFilename; }
    bool                        GetSyncMapElementData() const { return m_bSyncMapElementData; }
    void                        SetSyncMapElementData(bool bOn) { m_bSyncMapElementData = bOn; }
    bool                        GetBulletSyncEnabled() const { return m_bBulletSyncEnabled != 0; }
    int                         GetVehExtrapolatePercent() const { return m_iVehExtrapolatePercent; }
    int                         GetVehExtrapolatePingLimit() const { return m_iVehExtrapolatePingLimit; }
    bool                        GetUseAltPulseOrder() const { return m_bUseAltPulseOrder != 0; }
    const SString&              GetLoadstringLogFilename() const { return m_strLoadstringLogFilename; }
    bool                        GetLoadstringLogEnabled() const { return !m_strLoadstringLogFilename.empty(); }
    bool                        GetCrashDumpUploadEnabled() const { return m_bCrashDumpUploadEnabled != 0; }
    bool                        GetFilterDuplicateLogLinesEnabled() const { return m_bFilterDuplicateLogLinesEnabled != 0; }
    bool                        IsAuthSerialGroup(const SString& strGroup) const { return ListContains(m_AuthSerialGroupList, strGroup); };
    bool                        IsAuthSerialHttpIpException(const SString& strIp) const { return ListContains(m_AuthSerialHttpIpExceptionList, strIp); }
    bool                        GetAuthSerialEnabled() const { return !m_AuthSerialGroupList.empty(); };
    bool                        GetAuthSerialHttpEnabled() const { return m_bAuthSerialHttpEnabled && GetAuthSerialEnabled(); };
    const std::vector<SString>& GetAuthSerialGroupList() const { return m_AuthSerialGroupList; }
    const std::vector<SString>& GetAuthSerialHttpIpExceptionList() const { return m_AuthSerialHttpIpExceptionList; }
    const std::vector<SString>& GetOwnerEmailAddressList() const { return m_OwnerEmailAddressList; }
    bool                        IsDatabaseCredentialsProtectionEnabled() const { return m_bDatabaseCredentialsProtectionEnabled != 0; }
    bool                        IsFakeLagCommandEnabled() const { return m_bFakeLagCommandEnabled != 0; }

    SString GetSetting(const SString& configSetting);
    bool    GetSetting(const SString& configSetting, SString& strValue);
    bool    SetSetting(const SString& configSetting, const SString& strValue, bool bSave);
    bool    GetSettingTable(const SString& strName, CLuaArguments* outTable);

    void               SetCommandLineParser(CCommandLineParser* pCommandLineParser);
    void               ApplyNetOptions();
    void               ApplyBandwidthReductionMode();
    void               ApplyThreadNetEnabled();
    void               SetFakeLag(int iPacketLoss, int iExtraPing, int iExtraPingVary, int iKBPSLimit);
    const SNetOptions& GetNetOptions() { return m_NetOptions; }

    const std::vector<SIntSetting>& GetIntSettingList();
    void                            OnTickRateChange();
    void                            OnAseSettingChange();

private:
    void RegisterCommand(const char* szName, FCommandHandler* pFunction, bool bRestricted);
    bool GetSettingTable(const SString& strName, const char** szAttribNames, uint uiNumAttribNames, CLuaArguments* outTable);
    bool AddMissingSettings();

    CConsole*           m_pConsole = nullptr;
    CLuaManager*        m_pLuaManager = nullptr;
    CXMLNode*           m_pRootNode = nullptr;
    CCommandLineParser* m_pCommandLineParser = nullptr;

    unsigned int  m_uiVoiceSampleRate = 0;
    unsigned char m_ucVoiceQuality = 0;
    unsigned int  m_uiVoiceBitrate = 0;

    bool                       m_bVoiceEnabled = false;
    std::string                m_strServerIP;
    std::string                m_strServerName;
    unsigned short             m_usServerPort = 0;
    unsigned int               m_uiHardMaxPlayers = 0;
    unsigned int               m_uiSoftMaxPlayers = 0;
    bool                       m_bHTTPEnabled = false;
    std::string                m_strPassword;
    int                        m_iAseMode = 0;
    int                        m_iUpdateCycleDatagramsLimit = 0;
    int                        m_iUpdateCycleMessagesLimit = 0;
    unsigned short             m_usHTTPPort = 0;
    eHTTPDownloadType          m_ucHTTPDownloadType = eHTTPDownloadType::HTTP_DOWNLOAD_DISABLED;
    std::string                m_strHTTPDownloadURL;
    int                        m_iHTTPMaxConnectionsPerClient = 0;
    int                        m_iHTTPThreadCount = 0;
    int                        m_iHTTPDosThreshold = 0;
    SString                    m_strHTTPDosExclude;
    int                        m_iEnableClientChecks = 0;
    std::string                m_strLogFile;
    std::string                m_strAuthFile;
    bool                       m_bJoinFloodProtectionEnabled = false;
    bool                       m_bScriptDebugLogEnabled = false;
    std::string                m_strScriptDebugLogFile;
    unsigned int               m_uiScriptDebugLogLevel = 0;
    std::string                m_strAccessControlListFile;
    bool                       m_bVerifySerials = false;
    unsigned short             m_usFPSLimit = 0;
    int                        m_bDontBroadcastLan = 0;
    std::set<SString>          m_DisableComboACMap;
    std::set<SString>          m_EnableDiagnosticMap;
    std::vector<SString>       m_AuthSerialGroupList;
    bool                       m_bAuthSerialHttpEnabled = false;
    std::vector<SString>       m_AuthSerialHttpIpExceptionList;
    std::vector<SString>       m_OwnerEmailAddressList;
    SString                    m_strMinClientVersion;
    SString                    m_strRecommendedClientVersion;
    SString                    m_strIdFile;
    SString                    m_strGlobalDatabasesPath;
    SString                    m_strSystemDatabasesPath;
    SString                    m_strBackupPath;
    SString                    m_strDbLogFilename;
    int                        m_iBackupInterval = 0;
    int                        m_iBackupAmount = 0;
    int                        m_iCompactInternalDatabases = 0;
    bool                       m_bDidBackup = false;
    SString                    m_strBandwidthReductionMode;
    int                        m_iPendingWorkToDoSleepTime = 0;
    int                        m_iNoWorkToDoSleepTime = 0;
    bool                       m_bThreadNetEnabled = false;
    bool                       m_bSyncMapElementData = false;
    int                        m_bBulletSyncEnabled = 0;
    std::map<SString, SString> m_TransientSettings;
    SNetOptions                m_NetOptions;
    int                        m_iVehExtrapolatePercent = 0;
    int                        m_iVehExtrapolatePingLimit = 0;
    int                        m_bUseAltPulseOrder = 0;
    int                        m_bNetAutoFilter = 0;
    SString                    m_strLoadstringLogFilename;
    int                        m_iMinClientVersionAutoUpdate = 0;
    int                        m_iServerLogicFpsLimit = 0;
    int                        m_bCrashDumpUploadEnabled = 0;
    int                        m_bFilterDuplicateLogLinesEnabled = 0;
    int                        m_bDatabaseCredentialsProtectionEnabled = 0;
    int                        m_bFakeLagCommandEnabled = 0;
};
