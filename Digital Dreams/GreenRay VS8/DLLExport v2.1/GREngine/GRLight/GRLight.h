/*******************************************************************************
// It's Unofficial Version Of The GreenRay Engine v.1.0.0.3
// GRLight.h
// It's The GreenRay Direct3D Light Effects Engine Header File.
// Made Specially For Implementing 3DEngine Parameters.
// Date Creation: 29 August 2005
// Last Changing: 4 January 2006
// Author Rights By: Zie Technology, Zombie Soft And Lucky's Flash Studio Inc.,
// Licensed By: (C)DDD Digital Dreams Development Inc., 2006
*******************************************************************************/
#include <Form_Layer.h>
#include <GRModels.h>

//Exports..
//Setting Up Light Preferences
void SetLightPreferences(D3DLIGHT9& _pLight,D3DLIGHTTYPE _Type,float x,float y,float z);
void RenderLight(LPDIRECT3DDEVICE9 pDevice); //Output RenderingLight Directive