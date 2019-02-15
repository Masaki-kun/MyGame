//========================================================================================
// 
// [number.cpp]  Author : Masaki Kuboki
// 
//========================================================================================
#include "Number.h"
#include "2D.h"
#include "Manager.h"

//======================================================================================================
// 
//  •`‰æ
// 
//======================================================================================================
void CSceneNumber::Draw(int num, D3DCOLOR color, float posX, float posY, float scaleX, float scaleY)
{

	switch (num)
	{
	case 0:
		C2D::Draw(TEXTURE_NUMBER, 0, 0, 150, 282, color, 0.0f, 0.0f, scaleX, scaleY, { posX,posY,0.0f }, true);
		break;												       												 
															       												 
	case 1:		
		C2D::Draw(TEXTURE_NUMBER, 150, 0, 150, 282, color, 0.0f, 0.0f, scaleX, scaleY, { posX,posY,0.0f }, true);
		break;																	
																				
	case 2:		
		C2D::Draw(TEXTURE_NUMBER, 300, 0, 150, 282, color, 0.0f, 0.0f, scaleX, scaleY, { posX,posY,0.0f }, true);
		break;													   				
																   				
	case 3:		
		C2D::Draw(TEXTURE_NUMBER, 450, 0, 150, 282, color, 0.0f, 0.0f, scaleX, scaleY, { posX,posY,0.0f }, true);
		break;													   						
																   						
	case 4:		
		C2D::Draw(TEXTURE_NUMBER, 600, 0, 150, 282, color, 0.0f, 0.0f, scaleX, scaleY, { posX,posY,0.0f }, true);
		break;													   			
																   			
	case 5:	
		C2D::Draw(TEXTURE_NUMBER, 0, 282, 150, 282, color, 0.0f, 0.0f, scaleX, scaleY, { posX,posY,0.0f }, true);
		break;																			
																						
	case 6:	
		C2D::Draw(TEXTURE_NUMBER, 150, 282, 150, 282, color, 0.0f, 0.0f, scaleX, scaleY, { posX,posY,0.0f }, true);
		break;																	
																				
	case 7:		
		C2D::Draw(TEXTURE_NUMBER, 300, 282, 150, 282, color, 0.0f, 0.0f, scaleX, scaleY, { posX,posY,0.0f }, true);
		break;																		
																					
	case 8:		
		C2D::Draw(TEXTURE_NUMBER, 450, 282, 150, 282, color, 0.0f, 0.0f, scaleX, scaleY, { posX,posY,0.0f }, true);
		break;																	
																				
	case 9:			
		C2D::Draw(TEXTURE_NUMBER, 600, 282, 150, 282, color, 0.0f, 0.0f, scaleX, scaleY, { posX,posY,0.0f }, true);
		break;	

	case 10:
		C2D::Draw(TEXTURE_MINUTE, 0, 0, 150, 282,    color, 0.0f, 0.0f, scaleX, scaleY, { posX,posY,0.0f }, true);
		break;
																																															
	}																											
}					

