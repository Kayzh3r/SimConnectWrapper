#pragma once

#include <map>
#include <utility>

//-----------------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------------

// The external sim client GUID, used to register with SimConnect
// {3E6B47E7-C706-4A10-BC88-6E7C199ED5A6}
static const GUID g_guidSimConnectWrapper = 
{ 0x3e6b47e7, 0xc706, 0x4a10, { 0xbc, 0x88, 0x6e, 0x7c, 0x19, 0x9e, 0xd5, 0xa6 } };

//-----------------------------------------------------------------------------
// Data Defintiions
//-----------------------------------------------------------------------------

#pragma pack(push,1)

struct PerVehicleSimulate
{
    double Lat;
    double Lon;
    double Alt;
    double Pitch;
    double Bank;
    double Heading;
    double GroundAlt;
    double BathAlt;
    DWORD eSurfaceType;
};

struct PerVehicleOutput
{
    double Lat;
    double Lon;
    double Alt;
    double Pitch;
    double Bank;
    double Heading;
    double BodyVelX;
    double BodyVelY;
    double BodyVelZ;
    double WorldVelX;
    double WorldVelY;
    double WorldVelZ;
    double VerticalSpeed;
};

#pragma pack(pop)


