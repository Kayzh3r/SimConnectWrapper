// SimConnectWrapper.cpp : Test the SimConnect External Sim APIs
//

#include "stdafx.h"
#include "SimConnect.h"
#include "SimConnectWrapper.h"

HANDLE g_hSimConnect = NULL;

#define EXTERNAL_SIM_CALLBACK_MASK (SIMCONNECT_EXTERNAL_SIM_CALLBACK_FLAG_CREATE | SIMCONNECT_EXTERNAL_SIM_CALLBACK_FLAG_DESTROY | SIMCONNECT_EXTERNAL_SIM_CALLBACK_FLAG_SIMULATE | SIMCONNECT_EXTERNAL_SIM_CALLBACK_FLAG_LOCATION_CHANGED | SIMCONNECT_EXTERNAL_SIM_CALLBACK_FLAG_EVENT)

void __stdcall DLLStart( void )
{
    // open connection to local SimConnect server
    if ( SUCCEEDED(SimConnect_Open(&g_hSimConnect, ("SimConnectWrapper"), NULL, 0, NULL, SIMCONNECT_OPEN_CONFIGINDEX_LOCAL)) && g_hSimConnect != NULL)
    {
    }
}

void __stdcall DLLStop( void )
{
    if (g_hSimConnect != NULL)
    {
        SimConnect_Close(g_hSimConnect);
        g_hSimConnect = NULL;
    }
}

SIMCONNECTAPI _SimConnect_CallDispatch(DispatchProc pfcnDispatch, void * pContext)
{
	return SimConnect_CallDispatch(g_hSimConnect, pfcnDispatch, pContext);
}

SIMCONNECTAPI _SimConnect_RetrieveString(SIMCONNECT_RECV * pData, DWORD cbData, void * pStringV, char ** pszString, DWORD * pcbString)
{
	return SimConnect_RetrieveString(pData, cbData, pStringV, pszString, pcbString);
}

SIMCONNECTAPI _SimConnect_GetLastSentPacketID(DWORD * pdwError)
{
	return SimConnect_GetLastSentPacketID(g_hSimConnect, pdwError);
}

SIMCONNECTAPI _SimConnect_GetNextDispatch(SIMCONNECT_RECV ** ppData, DWORD * pcbData)
{
	return SimConnect_GetNextDispatch(g_hSimConnect, ppData, pcbData);
}

SIMCONNECTAPI _SimConnect_RequestResponseTimes(DWORD nCount, float * fElapsedSeconds)
{
	return SimConnect_RequestResponseTimes(g_hSimConnect, nCount, fElapsedSeconds);
}

SIMCONNECTAPI _SimConnect_InsertString(BYTE * pDest, DWORD cbDest, BYTE ** ppEnd, DWORD * pcbStringV, const char * pSource)
{
	return SimConnect_InsertString(pDest, cbDest, ppEnd, pcbStringV, pSource);
}

SIMCONNECTAPI _SimConnect_MapClientEventToSimEvent(SIMCONNECT_CLIENT_EVENT_ID EventID, const char * EventName = "")
{
	return SimConnect_MapClientEventToSimEvent(g_hSimConnect, EventID, EventName);
}

SIMCONNECTAPI _SimConnect_TransmitClientEvent(SIMCONNECT_OBJECT_ID ObjectID, SIMCONNECT_CLIENT_EVENT_ID EventID, DWORD dwData, SIMCONNECT_NOTIFICATION_GROUP_ID GroupID, SIMCONNECT_EVENT_FLAG Flags)
{
	return SimConnect_TransmitClientEvent(g_hSimConnect, ObjectID, EventID, dwData, GroupID, Flags);
}

SIMCONNECTAPI _SimConnect_SetSystemEventState(SIMCONNECT_CLIENT_EVENT_ID EventID, SIMCONNECT_STATE dwState)
{
	return SimConnect_SetSystemEventState(g_hSimConnect, EventID, dwState);
}

SIMCONNECTAPI _SimConnect_AddClientEventToNotificationGroup(SIMCONNECT_NOTIFICATION_GROUP_ID GroupID, SIMCONNECT_CLIENT_EVENT_ID EventID, BOOL bMaskable = FALSE)
{
	return SimConnect_AddClientEventToNotificationGroup(g_hSimConnect, GroupID, EventID, bMaskable);
}

SIMCONNECTAPI _SimConnect_RemoveClientEvent(SIMCONNECT_NOTIFICATION_GROUP_ID GroupID, SIMCONNECT_CLIENT_EVENT_ID EventID)
{
	return SimConnect_RemoveClientEvent(g_hSimConnect, GroupID, EventID);
}

SIMCONNECTAPI _SimConnect_SetNotificationGroupPriority(SIMCONNECT_NOTIFICATION_GROUP_ID GroupID, DWORD uPriority)
{
	return SimConnect_SetNotificationGroupPriority(g_hSimConnect, GroupID, uPriority);
}

SIMCONNECTAPI _SimConnect_ClearNotificationGroup(SIMCONNECT_NOTIFICATION_GROUP_ID GroupID)
{
	return SimConnect_ClearNotificationGroup(g_hSimConnect, GroupID);
}

SIMCONNECTAPI _SimConnect_RequestNotificationGroup(SIMCONNECT_NOTIFICATION_GROUP_ID GroupID, DWORD dwReserved = 0, DWORD Flags = 0)
{
	return SimConnect_RequestNotificationGroup(g_hSimConnect, GroupID, dwReserved, Flags);
}

SIMCONNECTAPI _SimConnect_AddToDataDefinition(SIMCONNECT_DATA_DEFINITION_ID DefineID, const char * DatumName, const char * UnitsName, SIMCONNECT_DATATYPE DatumType = SIMCONNECT_DATATYPE_FLOAT64, float fEpsilon = 0, DWORD DatumID = SIMCONNECT_UNUSED)
{
	return SimConnect_AddToDataDefinition(g_hSimConnect, DefineID, DatumName, UnitsName, DatumType, fEpsilon, DatumID);
}

SIMCONNECTAPI _SimConnect_ClearDataDefinition(SIMCONNECT_DATA_DEFINITION_ID DefineID)
{
	return SimConnect_ClearDataDefinition(g_hSimConnect, DefineID);
}

SIMCONNECTAPI _SimConnect_RequestDataOnSimObject(SIMCONNECT_DATA_REQUEST_ID RequestID, SIMCONNECT_DATA_DEFINITION_ID DefineID, SIMCONNECT_OBJECT_ID ObjectID, SIMCONNECT_PERIOD Period, SIMCONNECT_DATA_REQUEST_FLAG Flags = 0, DWORD origin = 0, DWORD interval = 0, DWORD limit = 0)
{
	return SimConnect_RequestDataOnSimObject(g_hSimConnect, RequestID, DefineID, ObjectID, Period, Flags, origin, interval, limit);
}

SIMCONNECTAPI _SimConnect_RequestDataOnSimObjectType(SIMCONNECT_DATA_REQUEST_ID RequestID, SIMCONNECT_DATA_DEFINITION_ID DefineID, DWORD dwRadiusMeters, SIMCONNECT_SIMOBJECT_TYPE type)
{
	return SimConnect_RequestDataOnSimObjectType(g_hSimConnect, RequestID, DefineID, dwRadiusMeters, type);
}

SIMCONNECTAPI _SimConnect_SetDataOnSimObject(SIMCONNECT_DATA_DEFINITION_ID DefineID, SIMCONNECT_OBJECT_ID ObjectID, SIMCONNECT_DATA_SET_FLAG Flags, DWORD ArrayCount, DWORD cbUnitSize, void * pDataSet)
{
	return SimConnect_SetDataOnSimObject(g_hSimConnect, DefineID, ObjectID, Flags, ArrayCount, cbUnitSize, pDataSet);
}

SIMCONNECTAPI _SimConnect_MapInputEventToClientEvent(SIMCONNECT_INPUT_GROUP_ID GroupID, const char * szInputDefinition, SIMCONNECT_CLIENT_EVENT_ID DownEventID, DWORD DownValue = 0, SIMCONNECT_CLIENT_EVENT_ID UpEventID = (SIMCONNECT_CLIENT_EVENT_ID)SIMCONNECT_UNUSED, DWORD UpValue = 0, BOOL bMaskable = FALSE)
{
	return SimConnect_MapInputEventToClientEvent(g_hSimConnect, GroupID, szInputDefinition, DownEventID, DownValue, UpEventID, UpValue, bMaskable);
}

SIMCONNECTAPI _SimConnect_SetInputGroupPriority(SIMCONNECT_INPUT_GROUP_ID GroupID, DWORD uPriority)
{
	return SimConnect_SetInputGroupPriority(g_hSimConnect, GroupID, uPriority);
}

SIMCONNECTAPI _SimConnect_RemoveInputEvent(SIMCONNECT_INPUT_GROUP_ID GroupID, const char * szInputDefinition)
{
	return SimConnect_RemoveInputEvent(g_hSimConnect, GroupID, szInputDefinition);
}

SIMCONNECTAPI _SimConnect_ClearInputGroup(SIMCONNECT_INPUT_GROUP_ID GroupID)
{
	return SimConnect_ClearInputGroup(g_hSimConnect, GroupID);
}

SIMCONNECTAPI _SimConnect_SetInputGroupState(SIMCONNECT_INPUT_GROUP_ID GroupID, DWORD dwState)
{
	return SimConnect_SetInputGroupState(g_hSimConnect, GroupID, dwState);
}

SIMCONNECTAPI _SimConnect_RequestReservedKey(SIMCONNECT_CLIENT_EVENT_ID EventID, const char * szKeyChoice1 = "", const char * szKeyChoice2 = "", const char * szKeyChoice3 = "")
{
	return SimConnect_RequestReservedKey(g_hSimConnect, EventID, szKeyChoice1, szKeyChoice2, szKeyChoice3);
}

SIMCONNECTAPI _SimConnect_SubscribeToSystemEvent(SIMCONNECT_CLIENT_EVENT_ID EventID, const char * SystemEventName)
{
	return SimConnect_SubscribeToSystemEvent(g_hSimConnect, EventID, SystemEventName);
}

SIMCONNECTAPI _SimConnect_UnsubscribeFromSystemEvent(SIMCONNECT_CLIENT_EVENT_ID EventID)
{
	return SimConnect_UnsubscribeFromSystemEvent(g_hSimConnect, EventID);
}

SIMCONNECTAPI _SimConnect_WeatherRequestInterpolatedObservation(SIMCONNECT_DATA_REQUEST_ID RequestID, float lat, float lon, float alt)
{
	return SimConnect_WeatherRequestInterpolatedObservation(g_hSimConnect, RequestID, lat, lon, alt);
}

SIMCONNECTAPI _SimConnect_WeatherRequestObservationAtStation(SIMCONNECT_DATA_REQUEST_ID RequestID, const char * szICAO)
{
	return SimConnect_WeatherRequestObservationAtStation(g_hSimConnect, RequestID, szICAO);
}

SIMCONNECTAPI _SimConnect_WeatherRequestObservationAtNearestStation(SIMCONNECT_DATA_REQUEST_ID RequestID, float lat, float lon)
{
	return SimConnect_WeatherRequestObservationAtNearestStation(g_hSimConnect, RequestID, lat, lon);
}

SIMCONNECTAPI _SimConnect_WeatherCreateStation(SIMCONNECT_DATA_REQUEST_ID RequestID, const char * szICAO, const char * szName, float lat, float lon, float alt)
{
	return SimConnect_WeatherCreateStation(g_hSimConnect, RequestID, szICAO, szName, lat, lon, alt);
}

SIMCONNECTAPI _SimConnect_WeatherRemoveStation(SIMCONNECT_DATA_REQUEST_ID RequestID, const char * szICAO)
{
	return SimConnect_WeatherRemoveStation(g_hSimConnect, RequestID, szICAO);
}

SIMCONNECTAPI _SimConnect_WeatherSetObservation(DWORD Seconds, const char * szMETAR)
{
	return SimConnect_WeatherSetObservation(g_hSimConnect, Seconds, szMETAR);
}

SIMCONNECTAPI _SimConnect_WeatherSetModeServer(DWORD dwPort, DWORD dwSeconds)
{
	return SimConnect_WeatherSetModeServer(g_hSimConnect, dwPort, dwSeconds);
}

SIMCONNECTAPI _SimConnect_WeatherSetModeTheme(const char * szThemeName)
{
	return SimConnect_WeatherSetModeTheme(g_hSimConnect, szThemeName);
}

SIMCONNECTAPI _SimConnect_WeatherSetModeGlobal()
{
	return SimConnect_WeatherSetModeGlobal(g_hSimConnect);
}

SIMCONNECTAPI _SimConnect_WeatherSetModeCustom()
{
	return SimConnect_WeatherSetModeCustom(g_hSimConnect);
}

SIMCONNECTAPI _SimConnect_WeatherSetDynamicUpdateRate(DWORD dwRate)
{
	return SimConnect_WeatherSetDynamicUpdateRate(g_hSimConnect, dwRate);
}

SIMCONNECTAPI _SimConnect_WeatherRequestCloudState(SIMCONNECT_DATA_REQUEST_ID RequestID, float minLat, float minLon, float minAlt, float maxLat, float maxLon, float maxAlt, DWORD dwFlags = 0)
{
	return SimConnect_WeatherRequestCloudState(g_hSimConnect, RequestID, minLat, minLon, minAlt, maxLat, maxLon, maxAlt, dwFlags);
}

SIMCONNECTAPI _SimConnect_WeatherCreateThermal(SIMCONNECT_DATA_REQUEST_ID RequestID, float lat, float lon, float alt, float radius, float height, float coreRate = 3.0f, float coreTurbulence = 0.05f, float sinkRate = 3.0f, float sinkTurbulence = 0.2f, float coreSize = 0.4f, float coreTransitionSize = 0.1f, float sinkLayerSize = 0.4f, float sinkTransitionSize = 0.1f)
{
	return SimConnect_WeatherCreateThermal(g_hSimConnect, RequestID, lat, lon, alt, radius, height, coreRate, coreTurbulence, sinkRate, sinkTurbulence, coreSize, coreTransitionSize, sinkLayerSize, sinkTransitionSize);
}

SIMCONNECTAPI _SimConnect_WeatherRemoveThermal(SIMCONNECT_OBJECT_ID ObjectID)
{
	return SimConnect_WeatherRemoveThermal(g_hSimConnect, ObjectID);
}

SIMCONNECTAPI _SimConnect_AICreateParkedATCAircraft(const char * szContainerTitle, const char * szTailNumber, const char * szAirportID, SIMCONNECT_DATA_REQUEST_ID RequestID)
{
	return SimConnect_AICreateParkedATCAircraft(g_hSimConnect, szContainerTitle, szTailNumber, szAirportID, RequestID);
}

SIMCONNECTAPI _SimConnect_AICreateEnrouteATCAircraft(const char * szContainerTitle, const char * szTailNumber, int iFlightNumber, const char * szFlightPlanPath, double dFlightPlanPosition, BOOL bTouchAndGo, SIMCONNECT_DATA_REQUEST_ID RequestID)
{
	return SimConnect_AICreateEnrouteATCAircraft(g_hSimConnect, szContainerTitle, szTailNumber, iFlightNumber, szFlightPlanPath, dFlightPlanPosition, bTouchAndGo, RequestID);
}

SIMCONNECTAPI _SimConnect_AICreateNonATCAircraft(const char * szContainerTitle, const char * szTailNumber, SIMCONNECT_DATA_INITPOSITION InitPos, SIMCONNECT_DATA_REQUEST_ID RequestID)
{
	return SimConnect_AICreateNonATCAircraft(g_hSimConnect, szContainerTitle, szTailNumber, InitPos, RequestID);
}

SIMCONNECTAPI _SimConnect_AICreateSimulatedObject(const char * szContainerTitle, SIMCONNECT_DATA_INITPOSITION InitPos, SIMCONNECT_DATA_REQUEST_ID RequestID)
{
	return SimConnect_AICreateSimulatedObject(g_hSimConnect, szContainerTitle, InitPos, RequestID);
}

SIMCONNECTAPI _SimConnect_AIReleaseControl(SIMCONNECT_OBJECT_ID ObjectID, SIMCONNECT_DATA_REQUEST_ID RequestID)
{
	return SimConnect_AIReleaseControl(g_hSimConnect, ObjectID, RequestID);
}

SIMCONNECTAPI _SimConnect_AIRemoveObject(SIMCONNECT_OBJECT_ID ObjectID, SIMCONNECT_DATA_REQUEST_ID RequestID)
{
	return SimConnect_AIRemoveObject(g_hSimConnect, ObjectID, RequestID);
}

SIMCONNECTAPI _SimConnect_AISetAircraftFlightPlan(SIMCONNECT_OBJECT_ID ObjectID, const char * szFlightPlanPath, SIMCONNECT_DATA_REQUEST_ID RequestID)
{
	return SimConnect_AISetAircraftFlightPlan(g_hSimConnect, ObjectID, szFlightPlanPath, RequestID);
}

SIMCONNECTAPI _SimConnect_ExecuteMissionAction(const GUID guidInstanceId)
{
	return SimConnect_ExecuteMissionAction(g_hSimConnect, guidInstanceId);
}

SIMCONNECTAPI _SimConnect_CompleteCustomMissionAction(const GUID guidInstanceId)
{
	return SimConnect_CompleteCustomMissionAction(g_hSimConnect, guidInstanceId);
}

SIMCONNECTAPI _SimConnect_CameraSetRelative6DOF(float fDeltaX, float fDeltaY, float fDeltaZ, float fPitchDeg, float fBankDeg, float fHeadingDeg)
{
	return SimConnect_CameraSetRelative6DOF(g_hSimConnect, fDeltaX, fDeltaY, fDeltaZ, fPitchDeg, fBankDeg, fHeadingDeg);
}

SIMCONNECTAPI _SimConnect_MenuAddItem(const char * szMenuItem, SIMCONNECT_CLIENT_EVENT_ID MenuEventID, DWORD dwData)
{
	return SimConnect_MenuAddItem(g_hSimConnect, szMenuItem, MenuEventID, dwData);
}

SIMCONNECTAPI _SimConnect_MenuDeleteItem(SIMCONNECT_CLIENT_EVENT_ID MenuEventID)
{
	return SimConnect_MenuDeleteItem(g_hSimConnect, MenuEventID);
}

SIMCONNECTAPI _SimConnect_MenuAddSubItem(SIMCONNECT_CLIENT_EVENT_ID MenuEventID, const char * szMenuItem, SIMCONNECT_CLIENT_EVENT_ID SubMenuEventID, DWORD dwData)
{
	return SimConnect_MenuAddSubItem(g_hSimConnect, MenuEventID, szMenuItem, SubMenuEventID, dwData);
}

SIMCONNECTAPI _SimConnect_MenuDeleteSubItem(SIMCONNECT_CLIENT_EVENT_ID MenuEventID, const SIMCONNECT_CLIENT_EVENT_ID SubMenuEventID)
{
	return SimConnect_MenuDeleteSubItem(g_hSimConnect, MenuEventID, SubMenuEventID);
}

SIMCONNECTAPI _SimConnect_RequestSystemState(SIMCONNECT_DATA_REQUEST_ID RequestID, const char * szState)
{
	return SimConnect_RequestSystemState(g_hSimConnect, RequestID, szState);
}

SIMCONNECTAPI _SimConnect_SetSystemState(const char * szState, DWORD dwInteger, float fFloat, const char * szString)
{
	return SimConnect_SetSystemState(g_hSimConnect, szState, dwInteger, fFloat, szString);
}

SIMCONNECTAPI _SimConnect_MapClientDataNameToID(const char * szClientDataName, SIMCONNECT_CLIENT_DATA_ID ClientDataID)
{
	return SimConnect_MapClientDataNameToID(g_hSimConnect, szClientDataName, ClientDataID);
}

SIMCONNECTAPI _SimConnect_CreateClientData(SIMCONNECT_CLIENT_DATA_ID ClientDataID, DWORD dwSize, SIMCONNECT_CREATE_CLIENT_DATA_FLAG Flags)
{
	return SimConnect_CreateClientData(g_hSimConnect, ClientDataID, dwSize, Flags);
}

SIMCONNECTAPI _SimConnect_AddToClientDataDefinition(SIMCONNECT_CLIENT_DATA_DEFINITION_ID DefineID, DWORD dwOffset, DWORD dwSizeOrType, float fEpsilon = 0, DWORD DatumID = SIMCONNECT_UNUSED)
{
	return SimConnect_AddToClientDataDefinition(g_hSimConnect, DefineID, dwOffset, dwSizeOrType, fEpsilon, DatumID);
}

SIMCONNECTAPI _SimConnect_ClearClientDataDefinition(SIMCONNECT_CLIENT_DATA_DEFINITION_ID DefineID)
{
	return SimConnect_ClearClientDataDefinition(g_hSimConnect, DefineID);
}

SIMCONNECTAPI _SimConnect_RequestClientData(SIMCONNECT_CLIENT_DATA_ID ClientDataID, SIMCONNECT_DATA_REQUEST_ID RequestID, SIMCONNECT_CLIENT_DATA_DEFINITION_ID DefineID, SIMCONNECT_CLIENT_DATA_PERIOD Period = SIMCONNECT_CLIENT_DATA_PERIOD_ONCE, SIMCONNECT_CLIENT_DATA_REQUEST_FLAG Flags = 0, DWORD origin = 0, DWORD interval = 0, DWORD limit = 0)
{
	return SimConnect_RequestClientData(g_hSimConnect, ClientDataID, RequestID, DefineID, Period, Flags, origin, interval, limit);
}

SIMCONNECTAPI _SimConnect_SetClientData(SIMCONNECT_CLIENT_DATA_ID ClientDataID, SIMCONNECT_CLIENT_DATA_DEFINITION_ID DefineID, SIMCONNECT_CLIENT_DATA_SET_FLAG Flags, DWORD dwReserved, DWORD cbUnitSize, void * pDataSet)
{
	return SimConnect_SetClientData(g_hSimConnect, ClientDataID, DefineID, Flags, dwReserved, cbUnitSize, pDataSet);
}

SIMCONNECTAPI _SimConnect_FlightLoad(const char * szFileName)
{
	return SimConnect_FlightLoad(g_hSimConnect, szFileName);
}

SIMCONNECTAPI _SimConnect_FlightSave(const char * szFileName, const char * szTitle, const char * szDescription, DWORD Flags)
{
	return SimConnect_FlightSave(g_hSimConnect, szFileName, szTitle, szDescription, Flags);
}

SIMCONNECTAPI _SimConnect_FlightPlanLoad(const char * szFileName)
{
	return SimConnect_FlightPlanLoad(g_hSimConnect, szFileName);
}

SIMCONNECTAPI _SimConnect_Text(SIMCONNECT_TEXT_TYPE type, float fTimeSeconds, SIMCONNECT_CLIENT_EVENT_ID EventID, DWORD cbUnitSize, void * pDataSet)
{
	return SimConnect_Text(g_hSimConnect, type, fTimeSeconds, EventID, cbUnitSize, pDataSet);
}

SIMCONNECTAPI _SimConnect_SubscribeToFacilities(SIMCONNECT_FACILITY_LIST_TYPE type, SIMCONNECT_DATA_REQUEST_ID RequestID)
{
	return SimConnect_SubscribeToFacilities(g_hSimConnect, type, RequestID);
}

SIMCONNECTAPI _SimConnect_UnsubscribeToFacilities(SIMCONNECT_FACILITY_LIST_TYPE type)
{
	return SimConnect_UnsubscribeToFacilities(g_hSimConnect, type);
}

SIMCONNECTAPI _SimConnect_RequestFacilitiesList(SIMCONNECT_FACILITY_LIST_TYPE type, SIMCONNECT_DATA_REQUEST_ID RequestID)
{
	return SimConnect_RequestFacilitiesList(g_hSimConnect, type, RequestID);
}

SIMCONNECTAPI _SimConnect_ChangeVehicle(const char * vehicleName)
{
	return SimConnect_ChangeVehicle(g_hSimConnect, vehicleName);
}

SIMCONNECTAPI _SimConnect_SetCameraRenderSettings(const GUID guidCamera, DWORD dwFlags)
{
	return SimConnect_SetCameraRenderSettings(g_hSimConnect, guidCamera, dwFlags);
}

SIMCONNECTAPI _SimConnect_SendCameraCommand(const GUID guidCamera, SIMCONNECT_CAMERA_COMMAND eCommand)
{
	return SimConnect_SendCameraCommand(g_hSimConnect, guidCamera, eCommand);
}

SIMCONNECTAPI _SimConnect_CreateObserver(const char * szName, SIMCONNECT_DATA_OBSERVER ObserverData)
{
	return SimConnect_CreateObserver(g_hSimConnect, szName, ObserverData);
}

SIMCONNECTAPI _SimConnect_RequestObserverData(SIMCONNECT_DATA_REQUEST_ID RequestID, const char * szName)
{
	return SimConnect_RequestObserverData(g_hSimConnect, RequestID, szName);
}

SIMCONNECTAPI _SimConnect_MoveObserver(const char * szName, SIMCONNECT_DATA_XYZ Translation)
{
	return SimConnect_MoveObserver(g_hSimConnect, szName, Translation);
}

SIMCONNECTAPI _SimConnect_RotateObserver(const char * szName, DWORD dwAxis, double dAngleDegrees)
{
	return SimConnect_RotateObserver(g_hSimConnect, szName, dwAxis, dAngleDegrees);
}

SIMCONNECTAPI _SimConnect_SetObserverPosition(const char * szName, SIMCONNECT_DATA_LATLONALT Position)
{
	return SimConnect_SetObserverPosition(g_hSimConnect, szName, Position);
}

SIMCONNECTAPI _SimConnect_SetObserverRotation(const char * szName, SIMCONNECT_DATA_PBH RotationAngles)
{
	return SimConnect_SetObserverRotation(g_hSimConnect, szName, RotationAngles);
}

SIMCONNECTAPI _SimConnect_SetObserverLookAt(const char * szName, SIMCONNECT_DATA_LATLONALT TargetPosition)
{
	return SimConnect_SetObserverLookAt(g_hSimConnect, szName, TargetPosition);
}

SIMCONNECTAPI _SimConnect_SetObserverFieldOfView(const char * szName, float fHorizontal, float fVertical)
{
	return SimConnect_SetObserverFieldOfView(g_hSimConnect, szName, fHorizontal, fVertical);
}

SIMCONNECTAPI _SimConnect_SetObserverStepSize(const char * szName, float fLinearStep, float fAngularStep)
{
	return SimConnect_SetObserverStepSize(g_hSimConnect, szName, fLinearStep, fAngularStep);
}

SIMCONNECTAPI _SimConnect_SetObserverFocalLength(const char * szName, float fFocalLength)
{
	return SimConnect_SetObserverFocalLength(g_hSimConnect, szName, fFocalLength);
}

SIMCONNECTAPI _SimConnect_SetObserverFocusFixed(const char * szName, BOOL bFocusFixed)
{
	return SimConnect_SetObserverFocusFixed(g_hSimConnect, szName, bFocusFixed);
}

SIMCONNECTAPI _SimConnect_SetObserverRegime(const char * szName, DWORD eRegime)
{
	return SimConnect_SetObserverRegime(g_hSimConnect, szName, eRegime);
}

SIMCONNECTAPI _SimConnect_SetObserverZoomLevels(const char * szName, DWORD dwNumLevels)
{
	return SimConnect_SetObserverZoomLevels(g_hSimConnect, szName, dwNumLevels);
}

SIMCONNECTAPI _SimConnect_RequestGroundInfo(SIMCONNECT_DATA_REQUEST_ID RequestID, double minLat, double minLon, double minAlt, double maxLat, double maxLon, double maxAlt, DWORD dwGridWidth, DWORD dwGridHeight, SIMCONNECT_GROUND_INFO_LATLON_FORMAT eLatLonFormat, SIMCONNECT_GROUND_INFO_ALT_FORMAT eAltFormat, SIMCONNECT_GROUND_INFO_SOURCE_FLAG eSourceFlags)
{
	return SimConnect_RequestGroundInfo(g_hSimConnect, RequestID, minLat, minLon, minAlt, maxLat, maxLon, maxAlt, dwGridWidth, dwGridHeight, eLatLonFormat, eAltFormat, eSourceFlags);
}

SIMCONNECTAPI _SimConnect_RequestGroundInfoOnSimObject(SIMCONNECT_DATA_REQUEST_ID RequestID, DWORD ObjectID, double offLat, double offsetLon, double offsetAlt, DWORD dwGridWidth, DWORD dwGridHeight, SIMCONNECT_GROUND_INFO_LATLON_FORMAT eLatLonFormat, SIMCONNECT_GROUND_INFO_ALT_FORMAT eAltFormat, SIMCONNECT_GROUND_INFO_SOURCE_FLAG eSourceFlags, SIMCONNECT_PERIOD Period, SIMCONNECT_DATA_REQUEST_FLAG Flags = 0, DWORD origin = 0, DWORD interval = 0, DWORD limit = 0)
{
	return SimConnect_RequestGroundInfoOnSimObject(g_hSimConnect, RequestID, ObjectID, offLat, offsetLon, offsetAlt, dwGridWidth, dwGridHeight, eLatLonFormat, eAltFormat, eSourceFlags, Period, Flags, origin, interval, limit);
}

SIMCONNECTAPI _SimConnect_RegisterExternalSim(const GUID guidExternalSimID, SIMCONNECT_EXTERNAL_SIM_CALLBACK_FLAG CallbackMask, SIMCONNECT_DATA_DEFINITION_ID DefineID)
{
	return SimConnect_RegisterExternalSim(g_hSimConnect, guidExternalSimID, CallbackMask, DefineID);
}

SIMCONNECTAPI _SimConnect_UnregisterExternalSim(const GUID guidExternalSimID)
{
	return SimConnect_UnregisterExternalSim(g_hSimConnect, guidExternalSimID);
}

SIMCONNECTAPI _SimConnect_RegisterExternalSecondarySim(const GUID guidExternalSecondarySimID, SIMCONNECT_EXTERNAL_SIM_CALLBACK_FLAG CallbackMask, SIMCONNECT_DATA_DEFINITION_ID DefineID)
{
	return SimConnect_RegisterExternalSecondarySim(g_hSimConnect, guidExternalSecondarySimID, CallbackMask, DefineID);
}

SIMCONNECTAPI _SimConnect_UnregisterExternalSecondarySim(const GUID guidExternalSecondarySimID)
{
	return SimConnect_UnregisterExternalSecondarySim(g_hSimConnect, guidExternalSecondarySimID);
}

SIMCONNECTAPI _SimConnect_AttachExternalSecondarySimToSimObject(DWORD dwObjectID, const GUID guidExternalSecondarySimID, const char * szExternalSimParams, DWORD dwExternalSimVarCount)
{
	return SimConnect_AttachExternalSecondarySimToSimObject(g_hSimConnect, dwObjectID, guidExternalSecondarySimID, szExternalSimParams, dwExternalSimVarCount);
}

SIMCONNECTAPI _SimConnect_DetachExternalSecondarySimFromSimObject(DWORD dwObjectID, const GUID guidExternalSecondarySimID)
{
	return SimConnect_DetachExternalSecondarySimFromSimObject(g_hSimConnect, dwObjectID, guidExternalSecondarySimID);
}

SIMCONNECTAPI _SimConnect_AICreateObjectWithExternalSim(const char * szContainerTitle, SIMCONNECT_DATA_INITPOSITION InitPos, SIMCONNECT_DATA_REQUEST_ID RequestID, const GUID guidExternalSimID, const char * szExternalSimParams, DWORD dwExternalSimVarCount)
{
	return SimConnect_AICreateObjectWithExternalSim(g_hSimConnect, szContainerTitle, InitPos, RequestID, guidExternalSimID, szExternalSimParams, dwExternalSimVarCount);
}

SIMCONNECTAPI _SimConnect_ChangeVehicleWithExternalSim(const char * szContainerTitle, const GUID guidExternalSimID, const char * szExternalSimParams, DWORD dwExternalSimVarCount)
{
	return SimConnect_ChangeVehicleWithExternalSim(g_hSimConnect, szContainerTitle, guidExternalSimID, szExternalSimParams, dwExternalSimVarCount);
}

SIMCONNECTAPI _SimConnect_RequestSynchronousBlock(SIMCONNECT_DATA_REQUEST_ID RequestID, SIMCONNECT_PERIOD Period, SIMCONNECT_DATA_REQUEST_FLAG Flags = 0, DWORD origin = 0, DWORD interval = 0, DWORD limit = 0)
{
	return SimConnect_RequestSynchronousBlock(g_hSimConnect, RequestID, Period, Flags, origin, interval, limit);
}

SIMCONNECTAPI _SimConnect_SynchronousUnblock()
{
	return SimConnect_SynchronousUnblock(g_hSimConnect);
}

SIMCONNECTAPI _SimConnect_SetSynchronousTimeout(float fTimeSeconds)
{
	return SimConnect_SetSynchronousTimeout(g_hSimConnect, fTimeSeconds);
}

SIMCONNECTAPI _SimConnect_SubscribeToSystemEventEx(SIMCONNECT_CLIENT_EVENT_ID EventID, const char * SystemEventName, SIMCONNECT_EVENT_SUBSCRIPTION_FLAG Flags)
{
	return SimConnect_SubscribeToSystemEventEx(g_hSimConnect, EventID, SystemEventName, Flags);
}

SIMCONNECTAPI _SimConnect_AttachObjectToSimObject(DWORD dwObjectID, SIMCONNECT_DATA_XYZ vecOff1, SIMCONNECT_DATA_PBH rotOff1, const char * szContainerTitle, SIMCONNECT_DATA_XYZ vecOff2, SIMCONNECT_DATA_PBH rotOff2, SIMCONNECT_DATA_REQUEST_ID RequestID)
{
	return SimConnect_AttachObjectToSimObject(g_hSimConnect, dwObjectID, vecOff1, rotOff1, szContainerTitle, vecOff2, rotOff2, RequestID);
}

SIMCONNECTAPI _SimConnect_AttachSimObjectToSimObject(DWORD dwObjectID1, SIMCONNECT_DATA_XYZ vecOff1, SIMCONNECT_DATA_PBH rotOff1, DWORD dwObjectID2, SIMCONNECT_DATA_XYZ vecOff2, SIMCONNECT_DATA_PBH rotOff2)
{
	return SimConnect_AttachSimObjectToSimObject(g_hSimConnect, dwObjectID1, vecOff1, rotOff1, dwObjectID2, vecOff2, rotOff2);
}

SIMCONNECTAPI _SimConnect_ReleaseSimObjectFromSimObject(DWORD dwObjectID1, DWORD dwObjectID2)
{
	return SimConnect_ReleaseSimObjectFromSimObject(g_hSimConnect, dwObjectID1, dwObjectID2);
}

SIMCONNECTAPI _SimConnect_AISetGroundClamp(SIMCONNECT_OBJECT_ID ObjectID, BOOL bGroundClamp = TRUE)
{
	return SimConnect_AISetGroundClamp(g_hSimConnect, ObjectID, bGroundClamp);
}

SIMCONNECTAPI _SimConnect_SetCameraColorizationMode(const char * szName, int eColorizationMode)
{
	return SimConnect_SetCameraColorizationMode(g_hSimConnect, szName, eColorizationMode);
}

SIMCONNECTAPI _SimConnect_SetCameraSensorMode(const char * szName, SIMCONNECT_CAMERA_SENSOR_MODE eSensorMode)
{
	return SimConnect_SetCameraSensorMode(g_hSimConnect, szName, eSensorMode);
}

SIMCONNECTAPI _SimConnect_CreateEffect(const char * effectName, SIMCONNECT_DATA_LATLONALT TargetPosition, SIMCONNECT_DATA_XYZ offset, BOOL attachToSimObject, DWORD dwObjectID, SIMCONNECT_DATA_REQUEST_ID RequestID, int effectDuration = -1)
{
	return SimConnect_CreateEffect(g_hSimConnect, effectName, TargetPosition, offset, attachToSimObject, dwObjectID, RequestID, effectDuration);
}

SIMCONNECTAPI _SimConnect_RemoveEffect(const DWORD effectId)
{
	return SimConnect_RemoveEffect(g_hSimConnect, effectId);
}

SIMCONNECTAPI _SimConnect_AttachWeaponToObject(const char * szContainerTitle, DWORD dwObjectID, int hardpointIndex, int numOfRounds)
{
	return SimConnect_AttachWeaponToObject(g_hSimConnect, szContainerTitle, dwObjectID, hardpointIndex, numOfRounds);
}

SIMCONNECTAPI _SimConnect_ClearWeapons(DWORD dwObjectID)
{
	return SimConnect_ClearWeapons(g_hSimConnect, dwObjectID);
}

SIMCONNECTAPI _SimConnect_CreateCameraDefinition(const GUID guidCamera, SIMCONNECT_CAMERA_TYPE ViewType, const char * szTitle, SIMCONNECT_DATA_XYZ xyzBias, SIMCONNECT_DATA_PBH pbhBias)
{
	return SimConnect_CreateCameraDefinition(g_hSimConnect, guidCamera, ViewType, szTitle, xyzBias, pbhBias);
}

SIMCONNECTAPI _SimConnect_CreateCameraInstance(const GUID guidCamera, const char * szName, SIMCONNECT_OBJECT_ID dwObjectID, SIMCONNECT_DATA_REQUEST_ID RequestID)
{
	return SimConnect_CreateCameraInstance(g_hSimConnect, guidCamera, szName, dwObjectID, RequestID);
}

SIMCONNECTAPI _SimConnect_DeleteCameraInstance(const GUID guidCamera, UINT32 instanceId)
{
	return SimConnect_DeleteCameraInstance(g_hSimConnect, guidCamera, instanceId);
}

SIMCONNECTAPI _SimConnect_SetCameraHorizontalFov(const char * szName, float hFov)
{
	return SimConnect_SetCameraHorizontalFov(g_hSimConnect, szName, hFov);
}

SIMCONNECTAPI _SimConnect_SetCameraVerticalFov(const char * szName, float vFov)
{
	return SimConnect_SetCameraVerticalFov(g_hSimConnect, szName, vFov);
}

SIMCONNECTAPI _SimConnect_SetCameraFov(const char * szName, float hFov, float vFov)
{
	return SimConnect_SetCameraFov(g_hSimConnect, szName, hFov, vFov);
}

SIMCONNECTAPI _SimConnect_CameraSetRelative6DofByName(const char * szName, float fDeltaX, float fDeltaY, float fDeltaZ, float fPitchDeg, float fBankDeg, float fHeadingDeg)
{
	return SimConnect_CameraSetRelative6DofByName(g_hSimConnect, szName, fDeltaX, fDeltaY, fDeltaZ, fPitchDeg, fBankDeg, fHeadingDeg);
}

SIMCONNECTAPI _SimConnect_SetMainCameraSensorMode(SIMCONNECT_CAMERA_SENSOR_MODE eSensorMode)
{
	return SimConnect_SetMainCameraSensorMode(g_hSimConnect, eSensorMode);
}

SIMCONNECTAPI _SimConnect_SetMainCameraHorizontalFov(float hFov)
{
	return SimConnect_SetMainCameraHorizontalFov(g_hSimConnect, hFov);
}

SIMCONNECTAPI _SimConnect_SetMainCameraVerticalFov(float vFov)
{
	return SimConnect_SetMainCameraVerticalFov(g_hSimConnect, vFov);
}

SIMCONNECTAPI _SimConnect_SetMainCameraFov(float hFov, float vFov)
{
	return SimConnect_SetMainCameraFov(g_hSimConnect, hFov, vFov);
}

SIMCONNECTAPI _SimConnect_CameraZoomIn(const char * szName)
{
	return SimConnect_CameraZoomIn(g_hSimConnect, szName);
}

SIMCONNECTAPI _SimConnect_CameraZoomOut(const char * szName)
{
	return SimConnect_CameraZoomOut(g_hSimConnect, szName);
}

SIMCONNECTAPI _SimConnect_MainCameraZoomIn()
{
	return SimConnect_MainCameraZoomIn(g_hSimConnect);
}

SIMCONNECTAPI _SimConnect_MainCameraZoomOut()
{
	return SimConnect_MainCameraZoomOut(g_hSimConnect);
}

SIMCONNECTAPI _SimConnect_OpenView(const char * szName, const char * szTitle = NULL)
{
	return SimConnect_OpenView(g_hSimConnect, szName, szTitle);
}

SIMCONNECTAPI _SimConnect_CloseView(const char * szName)
{
	return SimConnect_CloseView(g_hSimConnect, szName);
}

SIMCONNECTAPI _SimConnect_UndockView(const char * szName)
{
	return SimConnect_UndockView(g_hSimConnect, szName);
}

SIMCONNECTAPI _SimConnect_DockView(const char * szName)
{
	return SimConnect_DockView(g_hSimConnect, szName);
}

SIMCONNECTAPI _SimConnect_SetCameraWindowPosition(const char * szName, UINT uX, UINT uY)
{
	return SimConnect_SetCameraWindowPosition(g_hSimConnect, szName, uX, uY);
}

SIMCONNECTAPI _SimConnect_SetCameraWindowSize(const char * szName, UINT uWidth, UINT uHeight)
{
	return SimConnect_SetCameraWindowSize(g_hSimConnect, szName, uWidth, uHeight);
}

SIMCONNECTAPI _SimConnect_ChangeView(const char * szName)
{
	return SimConnect_ChangeView(g_hSimConnect, szName);
}

SIMCONNECTAPI _SimConnect_AddPostProcess(const char * szCameraName, const char * szPostProcessName)
{
	return SimConnect_AddPostProcess(g_hSimConnect, szCameraName, szPostProcessName);
}

SIMCONNECTAPI _SimConnect_AddPostProcessMainCamera(const char * szPostProcessName)
{
	return SimConnect_AddPostProcessMainCamera(g_hSimConnect, szPostProcessName);
}

SIMCONNECTAPI _SimConnect_RemovePostProcess(const char * szCameraName, const char * szPostProcessName)
{
	return SimConnect_RemovePostProcess(g_hSimConnect, szCameraName, szPostProcessName);
}

SIMCONNECTAPI _SimConnect_RemovePostProcessMainCamera(const char * szPostProcessName)
{
	return SimConnect_RemovePostProcessMainCamera(g_hSimConnect, szPostProcessName);
}

SIMCONNECTAPI _SimConnect_CameraSmoothRelative6DOF(float fDeltaX, float fDeltaY, float fDeltaZ, float fPitchDeg, float fBankDeg, float fHeadingDeg, float fSmoothTime = 0)
{
	return SimConnect_CameraSmoothRelative6DOF(g_hSimConnect, fDeltaX, fDeltaY, fDeltaZ, fPitchDeg, fBankDeg, fHeadingDeg, fSmoothTime);
}

SIMCONNECTAPI _SimConnect_CameraSmoothRelative6DofByName(const char * szName, float fDeltaX, float fDeltaY, float fDeltaZ, float fPitchDeg, float fBankDeg, float fHeadingDeg, float fSmoothTime = 0)
{
	return SimConnect_CameraSmoothRelative6DofByName(g_hSimConnect, szName, fDeltaX, fDeltaY, fDeltaZ, fPitchDeg, fBankDeg, fHeadingDeg, fSmoothTime);
}

SIMCONNECTAPI _SimConnect_CameraPanToView(const char * szCameraName, const char * szTargetName, float fSmoothTime = 0)
{
	return SimConnect_CameraPanToView(g_hSimConnect, szCameraName, szTargetName, fSmoothTime);
}

SIMCONNECTAPI _SimConnect_MainCameraPanToView(const char * szTargetName, float fSmoothTime = 0)
{
	return SimConnect_MainCameraPanToView(g_hSimConnect, szTargetName, fSmoothTime);
}

SIMCONNECTAPI _SimConnect_AICreateSimulatedObjectEx(const char * szContainerTitle, SIMCONNECT_DATA_INITPOSITION InitPos, SIMCONNECT_DATA_REQUEST_ID RequestID, BOOL isDisabled = FALSE, int OwnerID = -1)
{
	return SimConnect_AICreateSimulatedObjectEx(g_hSimConnect, szContainerTitle, InitPos, RequestID, isDisabled, OwnerID);
}

SIMCONNECTAPI _SimConnect_AIReleaseControlEx(SIMCONNECT_OBJECT_ID ObjectID, SIMCONNECT_DATA_REQUEST_ID RequestID, BOOL destroyAI = FALSE)
{
	return SimConnect_AIReleaseControlEx(g_hSimConnect, ObjectID, RequestID, destroyAI);
}

SIMCONNECTAPI _SimConnect_ReportWeaponDamage(SIMCONNECT_DATA_OBJECT_DAMAGED_BY_WEAPON WeaponDamageData)
{
	return SimConnect_ReportWeaponDamage(g_hSimConnect, WeaponDamageData);
}

SIMCONNECTAPI _SimConnect_RequestVersion(SIMCONNECT_DATA_REQUEST_ID RequestID)
{
	return SimConnect_RequestVersion(g_hSimConnect, RequestID);
}

SIMCONNECTAPI _SimConnect_RequestSceneryComplexity(SIMCONNECT_DATA_REQUEST_ID RequestID)
{
	return SimConnect_RequestSceneryComplexity(g_hSimConnect, RequestID);
}

SIMCONNECTAPI _SimConnect_RequestShadowFlags(SIMCONNECT_DATA_REQUEST_ID RequestID)
{
	return SimConnect_RequestShadowFlags(g_hSimConnect, RequestID);
}

SIMCONNECTAPI _SimConnect_ObserverTrackEntityOn(const char * szName, DWORD dwObjectID)
{
	return SimConnect_ObserverTrackEntityOn(g_hSimConnect, szName, dwObjectID);
}

SIMCONNECTAPI _SimConnect_ObserverTrackEntityOff(const char * szName)
{
	return SimConnect_ObserverTrackEntityOff(g_hSimConnect, szName);
}

SIMCONNECTAPI _SimConnect_ObserverAttachToEntityOn(const char * szName, DWORD dwObjectID, SIMCONNECT_DATA_XYZ Offset)
{
	return SimConnect_ObserverAttachToEntityOn(g_hSimConnect, szName, dwObjectID, Offset);
}

SIMCONNECTAPI _SimConnect_ObserverAttachToEntityOff(const char * szName)
{
	return SimConnect_ObserverAttachToEntityOff(g_hSimConnect, szName);
}

SIMCONNECTAPI _SimConnect_SetObserverLookAtEx(const char * szName, SIMCONNECT_DATA_LATLONALT TargetPosition)
{
	return SimConnect_SetObserverLookAtEx(g_hSimConnect, szName, TargetPosition);
}

SIMCONNECTAPI _SimConnect_RequestCameraFov(const char * szName, SIMCONNECT_DATA_REQUEST_ID RequestID)
{
	return SimConnect_RequestCameraFov(g_hSimConnect, szName, RequestID);
}

SIMCONNECTAPI _SimConnect_RequestCameraRelative6DOF(SIMCONNECT_DATA_REQUEST_ID RequestID)
{
	return SimConnect_RequestCameraRelative6DOF(g_hSimConnect, RequestID);
}

SIMCONNECTAPI _SimConnect_RequestCameraRelative6DofByName(const char * szName, SIMCONNECT_DATA_REQUEST_ID RequestID)
{
	return SimConnect_RequestCameraRelative6DofByName(g_hSimConnect, szName, RequestID);
}

SIMCONNECTAPI _SimConnect_RequestCameraSensorMode(const char * szName, SIMCONNECT_DATA_REQUEST_ID RequestID)
{
	return SimConnect_RequestCameraSensorMode(g_hSimConnect, szName, RequestID);
}

SIMCONNECTAPI _SimConnect_RequestCameraWindowPosition(const char * szName, SIMCONNECT_DATA_REQUEST_ID RequestID)
{
	return SimConnect_RequestCameraWindowPosition(g_hSimConnect, szName, RequestID);
}

SIMCONNECTAPI _SimConnect_RequestCameraWindowSize(const char * szName, SIMCONNECT_DATA_REQUEST_ID RequestID)
{
	return SimConnect_RequestCameraWindowSize(g_hSimConnect, szName, RequestID);
}

SIMCONNECTAPI _SimConnect_RequestMainCameraFov(SIMCONNECT_DATA_REQUEST_ID RequestID)
{
	return SimConnect_RequestMainCameraFov(g_hSimConnect, RequestID);
}

SIMCONNECTAPI _SimConnect_RequestMainCameraSensorMode(SIMCONNECT_DATA_REQUEST_ID RequestID)
{
	return SimConnect_RequestMainCameraSensorMode(g_hSimConnect, RequestID);
}

SIMCONNECTAPI _SimConnect_RequestGoalDataByGUID(SIMCONNECT_DATA_REQUEST_ID RequestID, const GUID guidInstanceID)
{
	return SimConnect_RequestGoalDataByGUID(g_hSimConnect, RequestID, guidInstanceID);
}

SIMCONNECTAPI _SimConnect_RequestGoalDataByIndex(SIMCONNECT_DATA_REQUEST_ID RequestID, int goalIndex)
{
	return SimConnect_RequestGoalDataByIndex(g_hSimConnect, RequestID, goalIndex);
}

SIMCONNECTAPI _SimConnect_ResolveGoal(const GUID guidInstanceID, SIMCONNECT_GOAL_RESOLUTION goalResolution)
{
	return SimConnect_ResolveGoal(g_hSimConnect, guidInstanceID, goalResolution);
}

SIMCONNECTAPI _SimConnect_RequestGoalCount(SIMCONNECT_DATA_REQUEST_ID RequestID)
{
	return SimConnect_RequestGoalCount(g_hSimConnect, RequestID);
}

SIMCONNECTAPI _SimConnect_RequestMissionObjectiveCount(SIMCONNECT_DATA_REQUEST_ID RequestID)
{
	return SimConnect_RequestMissionObjectiveCount(g_hSimConnect, RequestID);
}

SIMCONNECTAPI _SimConnect_RequestMissionObjectiveDataByGUID(SIMCONNECT_DATA_REQUEST_ID RequestID, const GUID guidInstanceID)
{
	return SimConnect_RequestMissionObjectiveDataByGUID(g_hSimConnect, RequestID, guidInstanceID);
}

SIMCONNECTAPI _SimConnect_RequestMissionObjectiveDataByIndex(SIMCONNECT_DATA_REQUEST_ID RequestID, int missionObjectiveIndex)
{
	return SimConnect_RequestMissionObjectiveDataByIndex(g_hSimConnect, RequestID, missionObjectiveIndex);
}

SIMCONNECTAPI _SimConnect_RequestFlightSegmentCount(SIMCONNECT_DATA_REQUEST_ID RequestID)
{
	return SimConnect_RequestFlightSegmentCount(g_hSimConnect, RequestID);
}

SIMCONNECTAPI _SimConnect_RequestFlightSegmentDataByGUID(SIMCONNECT_DATA_REQUEST_ID RequestID, const GUID guidInstanceID)
{
	return SimConnect_RequestFlightSegmentDataByGUID(g_hSimConnect, RequestID, guidInstanceID);
}

SIMCONNECTAPI _SimConnect_RequestFlightSegmentDataByIndex(SIMCONNECT_DATA_REQUEST_ID RequestID, int flightSegmentIndex)
{
	return SimConnect_RequestFlightSegmentDataByIndex(g_hSimConnect, RequestID, flightSegmentIndex);
}

SIMCONNECTAPI _SimConnect_RequestFlightSegmentRangeData(SIMCONNECT_DATA_REQUEST_ID RequestID, const GUID guidInstanceID, int rangeIndex)
{
	return SimConnect_RequestFlightSegmentRangeData(g_hSimConnect, RequestID, guidInstanceID, rangeIndex);
}

SIMCONNECTAPI _SimConnect_RequestChildGoalDataByIndex(SIMCONNECT_DATA_REQUEST_ID RequestID, const GUID parentGuidInstanceID, int goalIndex)
{
	return SimConnect_RequestChildGoalDataByIndex(g_hSimConnect, RequestID, parentGuidInstanceID, goalIndex);
}

SIMCONNECTAPI _SimConnect_GenerateFlightAnalysisDiagrams()
{
	return SimConnect_GenerateFlightAnalysisDiagrams(g_hSimConnect);
}

SIMCONNECTAPI _SimConnect_RequestLandingTriggerCount(SIMCONNECT_DATA_REQUEST_ID RequestID)
{
	return SimConnect_RequestLandingTriggerCount(g_hSimConnect, RequestID);
}

SIMCONNECTAPI _SimConnect_RequestLandingTriggerLandingInfoCount(SIMCONNECT_DATA_REQUEST_ID RequestID, int landingTriggerIndex)
{
	return SimConnect_RequestLandingTriggerLandingInfoCount(g_hSimConnect, RequestID, landingTriggerIndex);
}

SIMCONNECTAPI _SimConnect_RequestLandingTriggerLandingInfoByIndex(SIMCONNECT_DATA_REQUEST_ID RequestID, const GUID landingTriggerInstanceID, int landingIndex)
{
	return SimConnect_RequestLandingTriggerLandingInfoByIndex(g_hSimConnect, RequestID, landingTriggerInstanceID, landingIndex);
}

SIMCONNECTAPI _SimConnect_RequestSessionDuration(SIMCONNECT_DATA_REQUEST_ID RequestID)
{
	return SimConnect_RequestSessionDuration(g_hSimConnect, RequestID);
}

SIMCONNECTAPI _SimConnect_RequestAttachPointData(SIMCONNECT_DATA_REQUEST_ID RequestID, DWORD dwObjectID, const char * szAttachPointName, BOOL bRequestWorldCoordinates = FALSE)
{
	return SimConnect_RequestAttachPointData(g_hSimConnect, RequestID, dwObjectID, szAttachPointName, bRequestWorldCoordinates);
}

SIMCONNECTAPI _SimConnect_PlaybackRecording(const char * szFileName, int bookmarkIndex, double endTimeInSeconds)
{
	return SimConnect_PlaybackRecording(g_hSimConnect, szFileName, bookmarkIndex, endTimeInSeconds);
}

SIMCONNECTAPI _SimConnect_StartRecorder()
{
	return SimConnect_StartRecorder(g_hSimConnect);
}

SIMCONNECTAPI _SimConnect_StopRecorderAndSaveRecording(const char * szTitle, const char * szDescription, BOOL promptUser)
{
	return SimConnect_StopRecorderAndSaveRecording(g_hSimConnect, szTitle, szDescription, promptUser);
}

SIMCONNECTAPI _SimConnect_RequestRecordingInfo(SIMCONNECT_DATA_REQUEST_ID RequestID, const char * szFileName)
{
	return SimConnect_RequestRecordingInfo(g_hSimConnect, RequestID, szFileName);
}

SIMCONNECTAPI _SimConnect_RequestBookmarkInfo(SIMCONNECT_DATA_REQUEST_ID RequestID, const char * szFileName, int bookmarkIndex)
{
	return SimConnect_RequestBookmarkInfo(g_hSimConnect, RequestID, szFileName, bookmarkIndex);
}

SIMCONNECTAPI _SimConnect_ObserverTrackLocationOn(const char * szName, SIMCONNECT_DATA_LATLONALT TargetPosition)
{
	return SimConnect_ObserverTrackLocationOn(g_hSimConnect, szName, TargetPosition);
}

SIMCONNECTAPI _SimConnect_ObserverTrackLocationOff(const char * szName)
{
	return SimConnect_ObserverTrackLocationOff(g_hSimConnect, szName);
}

SIMCONNECTAPI _SimConnect_SetObserverSceneryOrigin(const char * szName, DWORD eOrigin)
{
	return SimConnect_SetObserverSceneryOrigin(g_hSimConnect, szName, eOrigin);
}

SIMCONNECTAPI _SimConnect_RequestTrafficSettings(SIMCONNECT_DATA_REQUEST_ID RequestID)
{
	return SimConnect_RequestTrafficSettings(g_hSimConnect, RequestID);
}

SIMCONNECTAPI _SimConnect_SetTrafficSettings(UINT uAirlineDensity, UINT uGADensity, UINT uRoadTrafficDensity, UINT uShipsAndFerriesDensity, UINT uLeisureBoatDensity, SIMCONNECT_DYNAMIC_FREQUENCY eAirportVehicleDensity, BOOL bIFROnly)
{
	return SimConnect_SetTrafficSettings(g_hSimConnect, uAirlineDensity, uGADensity, uRoadTrafficDensity, uShipsAndFerriesDensity, uLeisureBoatDensity, eAirportVehicleDensity, bIFROnly);
}

SIMCONNECTAPI _SimConnect_RequestJoystickDeviceInfo(SIMCONNECT_DATA_REQUEST_ID RequestID)
{
	return SimConnect_RequestJoystickDeviceInfo(g_hSimConnect, RequestID);
}

SIMCONNECTAPI _SimConnect_RequestMobileSceneryInRadius(SIMCONNECT_DATA_REQUEST_ID RequestID, DWORD dwRadiusMeters)
{
	return SimConnect_RequestMobileSceneryInRadius(g_hSimConnect, RequestID, dwRadiusMeters);
}

SIMCONNECTAPI _SimConnect_RequestMobileSceneryDataByID(SIMCONNECT_DATA_REQUEST_ID RequestID, SIMCONNECT_OBJECT_ID ObjectID)
{
	return SimConnect_RequestMobileSceneryDataByID(g_hSimConnect, RequestID, ObjectID);
}

SIMCONNECTAPI _SimConnect_CaptureImage(const char * szFileName, const char * szFilePath, UINT uImageFormat, const char * szViewName, BOOL bFileNameContainsExtension = FALSE)
{
	return SimConnect_CaptureImage(g_hSimConnect, szFileName, szFilePath, uImageFormat, szViewName, bFileNameContainsExtension);
}

SIMCONNECTAPI _SimConnect_BeginVideoStream(const char * szViewName, SIMCONNECT_DATA_VIDEO_STREAM_INFO StreamInfo)
{
	return SimConnect_BeginVideoStream(g_hSimConnect, szViewName, StreamInfo);
}

SIMCONNECTAPI _SimConnect_EndVideoStream(const char * szViewName, SIMCONNECT_DATA_VIDEO_STREAM_INFO StreamInfo)
{
	return SimConnect_EndVideoStream(g_hSimConnect, szViewName, StreamInfo);
}