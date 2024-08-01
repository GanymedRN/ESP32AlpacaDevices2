/**************************************************************************************************
  Filename:       AlpacaFocuser.cpp
  Revised:        $Date: 2024-07-24$
  Revision:       $Revision: 01 $
  Description:    Common ASCOM Alpaca Focuser V3

  Copyright 2024 peter_n@gmx.de. All rights reserved.
**************************************************************************************************/
#include "AlpacaFocuser.h"

AlpacaFocuser::AlpacaFocuser()
{
    strlcpy(_device_type, ALPACA_FOCUSER_DEVICE_TYPE, sizeof(_device_type));
    strlcpy(_device_description, ALPACA_FOCUSER_DESCRIPTION, sizeof(_device_description));
    strlcpy(_driver_info, ALPACA_FOCUSER_DRIVER_INFO, sizeof(_driver_info));
    strlcpy(_driver_version, ALPACA_FOCUSER_DRIVER_VERSION, sizeof(_driver_version));
    _device_interface_version = ALPACA_FOCUSER_INTERFACE_VERSION;
}

void AlpacaFocuser::Begin()
{
    AlpacaDevice::Begin();
}

void AlpacaFocuser::RegisterCallbacks()
{
    AlpacaDevice::RegisterCallbacks();

#ifdef ALPACA_FOCUSER_PUT_ACTION_IMPLEMENTED
    this->createCallBack(LHF(AlpacaPutAction), HTTP_PUT, "action", false);
#endif    
#ifdef ALPACA_FOCUSER_PUT_COMMAND_BLIND_IMPLEMENTED
    this->createCallBack(LHF(AlpacaPutCommandBlind), HTTP_PUT, "commandblind", false);
#endif    
#ifdef ALPACA_FOCUSER_PUT_COMMAND_BOOL_IMPLEMENTED
    this->createCallBack(LHF(AlpacaPutCommandBool), HTTP_PUT, "commandbool", false);
#endif    
#ifdef ALPACA_FOCUSER_PUT_COMMAND_STRING_IMPLEMENTED
    this->createCallBack(LHF(AlpacaPutCommandString), HTTP_PUT, "commandstring", false);
#endif    

    this->createCallBack(LHF(_alpacaGetAbsolut), HTTP_GET, "absolute", false);
    this->createCallBack(LHF(_alpacaGetIsMoving), HTTP_GET, "ismoving", false);
    this->createCallBack(LHF(_alpacaGetMaxIncrement), HTTP_GET, "maxincrement", false);
    this->createCallBack(LHF(_alpacaGetMaxStep), HTTP_GET, "maxstep", false);
    this->createCallBack(LHF(_alpacaGetPosition), HTTP_GET, "position", false);
    this->createCallBack(LHF(_alpacaGetStepSize), HTTP_GET, "stepsize", false);
    this->createCallBack(LHF(_alpacaGetTempComp), HTTP_GET, "tempcomp", false);
    this->createCallBack(LHF(_alpacaGetTempCompAvailable), HTTP_GET, "tempcompavailable", false);
    this->createCallBack(LHF(_alpacaGetTemperature), HTTP_GET, "temperature", false);

    this->createCallBack(LHF(_alpacaPutTempComp), HTTP_PUT, "tempcomp", false);
    this->createCallBack(LHF(_alpacaPutHalt), HTTP_PUT, "halt", false);
    this->createCallBack(LHF(_alpacaPutMove), HTTP_PUT, "move", false);
}

void AlpacaFocuser::_alpacaGetAbsolut(AsyncWebServerRequest *request)
{
    DBG_FOCUSER_GET_ABSOLUT
    _service_counter++;
    bool absolut = false;
    _alpaca_server->RspStatusClear(_rsp_status);

    uint32_t client_idx = checkClientDataAndConnection(request, client_idx, Spelling_t::kIgnoreCase);
    if (client_idx > 0)
    {
        absolut = _getAbsolut();
    }
    _alpaca_server->Respond(request, _clients[client_idx], _rsp_status, (bool)absolut);
    DBG_END
}

void AlpacaFocuser::_alpacaGetIsMoving(AsyncWebServerRequest *request)
{
    DBG_FOCUSER_GET_IS_MOVING
    _service_counter++;
    bool is_moving = false;
    _alpaca_server->RspStatusClear(_rsp_status);

    uint32_t client_idx = checkClientDataAndConnection(request, client_idx, Spelling_t::kIgnoreCase);
    if (client_idx > 0)
    {
        is_moving = _getIsMoving();
    }
    _alpaca_server->Respond(request, _clients[client_idx], _rsp_status, (bool)is_moving);
    DBG_END
}

void AlpacaFocuser::_alpacaGetMaxIncrement(AsyncWebServerRequest *request)
{
    DBG_FOCUSER_GET_MAX_INCREMENT
    _service_counter++;
    int32_t max_increment = 0.0;
    _alpaca_server->RspStatusClear(_rsp_status);

    uint32_t client_idx = checkClientDataAndConnection(request, client_idx, Spelling_t::kIgnoreCase);
    if (client_idx > 0)
    {
        max_increment = _getMaxIncrement();
    }
    _alpaca_server->Respond(request, _clients[client_idx], _rsp_status, (int32_t)max_increment);
    DBG_END
}

void AlpacaFocuser::_alpacaGetMaxStep(AsyncWebServerRequest *request)
{
    DBG_FOCUSER_GET_MAX_STEP
    _service_counter++;
    int32_t max_step = 0.0;
    _alpaca_server->RspStatusClear(_rsp_status);

    uint32_t client_idx = checkClientDataAndConnection(request, client_idx, Spelling_t::kIgnoreCase);
    if (client_idx > 0)
    {
        max_step = _getMaxStep();
    }
    _alpaca_server->Respond(request, _clients[client_idx], _rsp_status, (int32_t)max_step);
    DBG_END
}

void AlpacaFocuser::_alpacaGetPosition(AsyncWebServerRequest *request)
{
    DBG_FOCUSER_GET_POSITION
    _service_counter++;
    int32_t position = false;
    _alpaca_server->RspStatusClear(_rsp_status);

    uint32_t client_idx = checkClientDataAndConnection(request, client_idx, Spelling_t::kIgnoreCase);
    if (client_idx > 0)
    {
        position = _getPosition();
    }
    _alpaca_server->Respond(request, _clients[client_idx], _rsp_status, (int32_t)position);
    DBG_END
}

void AlpacaFocuser::_alpacaGetStepSize(AsyncWebServerRequest *request)
{
    DBG_FOCUSER_GET_STEP_SIZE
    _service_counter++;
    double step_size = 0.0;
    _alpaca_server->RspStatusClear(_rsp_status);

    uint32_t client_idx = checkClientDataAndConnection(request, client_idx, Spelling_t::kIgnoreCase);
    if (client_idx > 0)
    {
        step_size = _getStepSize();
    }
    _alpaca_server->Respond(request, _clients[client_idx], _rsp_status, step_size);
    DBG_END
}

void AlpacaFocuser::_alpacaGetTempComp(AsyncWebServerRequest *request)
{
    DBG_FOCUSER_GET_TEMP_COMP
    _service_counter++;
    bool temp_comp = false;
    _alpaca_server->RspStatusClear(_rsp_status);

    uint32_t client_idx = checkClientDataAndConnection(request, client_idx, Spelling_t::kIgnoreCase);
    if (client_idx > 0)
    {
        temp_comp = _getTempComp();
    }
    _alpaca_server->Respond(request, _clients[client_idx], _rsp_status, (bool)temp_comp);
    DBG_END
}

void AlpacaFocuser::_alpacaGetTempCompAvailable(AsyncWebServerRequest *request)
{
    DBG_FOCUSER_GET_TEMP_COMP_AVAILABLE
    _service_counter++;
    bool temp_comp_available = false;
    _alpaca_server->RspStatusClear(_rsp_status);

    uint32_t client_idx = checkClientDataAndConnection(request, client_idx, Spelling_t::kIgnoreCase);
    if (client_idx > 0)
    {
        temp_comp_available = _getTempCompAvailable();
    }
    _alpaca_server->Respond(request, _clients[client_idx], _rsp_status, (bool)temp_comp_available);
    DBG_END
}

void AlpacaFocuser::_alpacaGetTemperature(AsyncWebServerRequest *request)
{
    DBG_FOCUSER_GET_TEMPERATUR
    _service_counter++;
    double temperature = false;
    _alpaca_server->RspStatusClear(_rsp_status);

    uint32_t client_idx = checkClientDataAndConnection(request, client_idx, Spelling_t::kIgnoreCase);
    if (client_idx > 0)
    {
        temperature = _getTemperature();
    }
    _alpaca_server->Respond(request, _clients[client_idx], _rsp_status, (double)temperature);
    DBG_END
}

void AlpacaFocuser::_alpacaPutTempComp(AsyncWebServerRequest *request)
{
    DBG_FOCUSER_PUT_TEMP_COMP;
    _service_counter++;
    uint32_t client_idx = 0;
    bool temp_comp = false;
    _alpaca_server->RspStatusClear(_rsp_status);

    try
    {
        if ((client_idx = checkClientDataAndConnection(request, client_idx, Spelling_t::kStrict)) == 0)
            throw(&_rsp_status);

        if (_alpaca_server->GetParam(request, "TempComp", temp_comp, Spelling_t::kStrict) == false)
            _alpaca_server->ThrowRspStatusParameterNotFound(request, _rsp_status, "TempComp");

        _putTempComp(temp_comp);
    }
    catch (AlpacaRspStatus_t *rspStatus)
    { // empty
    }
    _alpaca_server->Respond(request, _clients[client_idx], _rsp_status);
    DBG_END
};

void AlpacaFocuser::_alpacaPutHalt(AsyncWebServerRequest *request)
{
    DBG_FOCUSER_PUT_HALT;
    _service_counter++;
    _alpaca_server->RspStatusClear(_rsp_status);
    uint32_t id = 0;

    uint32_t client_idx = checkClientDataAndConnection(request, client_idx, Spelling_t::kIgnoreCase);
    if (client_idx > 0)
    {
        _putHalt();
    }
    _alpaca_server->Respond(request, _clients[client_idx], _rsp_status);
    DBG_END
};

void AlpacaFocuser::_alpacaPutMove(AsyncWebServerRequest *request)
{
    DBG_FOCUSER_PUT_MOVE;
    _service_counter++;
    uint32_t client_idx = 0;
    _alpaca_server->RspStatusClear(_rsp_status);
    int32_t position = 0;

    try
    {
        if ((client_idx = checkClientDataAndConnection(request, client_idx, Spelling_t::kStrict)) == 0)
            throw(&_rsp_status);

        if (_alpaca_server->GetParam(request, "Position", position, Spelling_t::kStrict) == false)
            _alpaca_server->ThrowRspStatusParameterNotFound(request, _rsp_status, "Position");

        _putMove(position);
    }
    catch (AlpacaRspStatus_t *rspStatus)
    { // empty
    }
    _alpaca_server->Respond(request, _clients[client_idx], _rsp_status);
    DBG_END
};