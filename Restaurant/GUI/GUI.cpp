#include "GUI.h"
#include <algorithm>
#include <stdio.h>
#pragma comment( lib, "Winmm.lib" )
//////////////////////////////////////////////////////////////////////////////////////////
GUI::GUI() : bufferSize(MAX_PATH)
{
	GetCurrentDirectory(bufferSize, oldDir);
	
	cout<<endl;
	MusicOn = false;
	GMode = MODE_DARK;
	GUIL = DARKGUIL;
	GUID = DARKGUID;
	GUIS = BLACK;
	GUIF = WHITE;
	GUIR = REDR;
	pWind = new window(WindWidth+10,WindHeight,0,0); 
	pWind->ChangeTitle("The Restautant");
	OrderCount = 0;
	//Set color for each order type
	OrdersClrs[TYPE_NRM] = 	NDARKBLUE;	//normal-order color
	OrdersClrs[TYPE_FROZ] = NVIOLET;		//Frozen-order color
	OrdersClrs[TYPE_VIP] = 	NRED;		//VIP-order color

	//Initializing the Number of Orders and Motors in each region
	ResetDrawNumbers();
	ClearMenuBar();
	ClearStatusBar();
	ClearDrawingArea(); 
	DrawRestArea();  
	CreateMenuBar();
	
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ChangeMode()
{
	if(GMode == MODE_LIGHT)
	{
		GMode = MODE_DARK;
		GUIL = DARKGUIL;
		GUID = DARKGUID;
		GUIS = BLACK;
		GUIF = WHITE;
		GUIR = REDR;
	}
	else
	{
		GMode = MODE_LIGHT;
		GUIL = LIGHTGUIL;
		GUID = LIGHTGUID;
		GUIS = WHITE;
		GUIF = BLACK;
		GUIR = BLUER;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
GUI::~GUI()
{
	delete pWind;
}

//////////////////////////////////////////////////////////////////////////////////////////
// ================================== INPUT FUNCTIONS ====================================
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::waitForClick() const
{
	int x,y;
	Sleep(50);
	pWind->FlushMouseQueue();
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}
//////////////////////////////////////////////////////////////////////////////////////////
string GUI::GetString() const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label += Key;
		
		PrintMessage(Label);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
// ================================== OUTPUT FUNCTIONS ===================================
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::PrintMessage(string line0, string line1, string line2, string line3, string line4) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(GUIR);
	pWind->SetFont(18, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(13, WindHeight - (StatusBarHeight - 11), line0); //First line 
	pWind->DrawString(10, WindHeight - (StatusBarHeight - 33), line1); //Second line
	pWind->DrawString(10, WindHeight - (StatusBarHeight - 55), line2); //Third line
	pWind->DrawString(10, WindHeight - (StatusBarHeight - 77), line3); //Fourth line 
	pWind->DrawString(10, WindHeight - (StatusBarHeight - 99), line4); //Fifth Line

}
void GUI::PrintMenuMessage(string msg) const
{
	ClearMenuBar();
	pWind->SetPen(GUIR);
	pWind->SetFont(24, BOLD , BY_NAME, "Arial"); 
	pWind->DrawString(10,10,msg);
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::PrintTime(int time, color clr) const	//Prints time on the Center
{
	string mn, secs;
	int mins = time / 60, seconds = time % 60;
	mn = (mins < 10) ? "0" + to_string(mins) : to_string(mins); secs = (seconds < 10) ? "0" + to_string(seconds) : to_string(seconds);
	if(clr!=RED)
		pWind->SetPen(GUIF);
	else
		pWind->SetPen(clr);
	pWind->SetFont(32, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(565, 260, mn + ":" + secs); 
	
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawString(const int iX, const int iY, const string Text)
{
	pWind->SetPen(DARKRED);
	pWind->SetFont(18, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(iX, iY, Text);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearMenuBar() const
{
	pWind->SetPen(GUID, 3);
	pWind->SetBrush(GUID);
	pWind->DrawRectangle(0, 0, WindWidth, MenuBarHeight);	
	pWind->SetPen(GUIS, 3);
	pWind->DrawLine(0, MenuBarHeight , WindWidth,MenuBarHeight);
		
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateMenuBar()
{
	string MenuItemImages[MENU_COUNT];
	string SwitchGUI;
	string Music;
	if(GMode == MODE_DARK)
	{
		MenuItemImages[INTERACTIVE] = "images\\interactive.jpg";
		MenuItemImages[STEPBYSTEP] = "images\\steps.jpg";
		MenuItemImages[SILENT] = "images\\silent.jpg";
		SwitchGUI = "images\\switch.jpg";
		Music = (MusicOn) ? "images\\offd.jpg" :"images\\ond.jpg";
	}
	else
	{
		MenuItemImages[INTERACTIVE] = "images\\interactivel.jpg";
		MenuItemImages[STEPBYSTEP] = "images\\stepsl.jpg";
		MenuItemImages[SILENT] = "images\\silentl.jpg";
		SwitchGUI = "images\\switchl.jpg";
		Music = (MusicOn) ? "images\\offl.jpg" :"images\\onl.jpg";
	}
	
	for(int i=0; i<MENU_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*MenuItemWidth, 0, MenuItemWidth, 50);
	pWind->DrawImage(SwitchGUI,WindWidth-120, 0, 120, 50);
	pWind->DrawImage(Music,WindWidth-120 * 2, 0, 120, 50);
	pWind->SetPen(GUIS, 3);
	pWind->DrawLine(0, MenuBarHeight , WindWidth,MenuBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusBar() const
{
	pWind->SetPen(GUID, 3);
	pWind->SetBrush(GUID);
	pWind->DrawRectangle(0, WindHeight - StatusBarHeight , WindWidth, WindHeight);	

	pWind->SetPen(GUIS, 3);
	pWind->DrawLine(0, WindHeight - StatusBarHeight , WindWidth, WindHeight - StatusBarHeight);	
}
///////////////////////////////////////////////////////////////////////////////////
void GUI::ClearDrawingArea() const
{
	// Clearing the Drawing area
	pWind->SetPen(GUIL, 3);
	pWind->SetBrush(GUIL);
	pWind->DrawRectangle(0, MenuBarHeight, WindWidth, WindHeight - StatusBarHeight);
}
///////////////////////////////////////////////////////////////////////////////////
void GUI::DrawRestArea() const
{
	int L = RestWidth / 2;

	// 1- Drawing the brown square of the Rest
	pWind->SetPen(GUID);
	pWind->SetBrush(GUID);
	//Dark Circle;
	pWind->DrawCircle(600,275,120);

	// 2- Drawing the 2 brown crossed lines (for making 4 regions)
	pWind->SetPen(GUID, 5);
	pWind->DrawLine(0, YHalfDrawingArea, WindWidth, YHalfDrawingArea);
	pWind->DrawLine(WindWidth/2, MenuBarHeight, WindWidth/2, WindHeight-StatusBarHeight);

	// 3- Drawing the 2 white crossed lines (inside the Rest)
	pWind->SetPen(GUID,5);
	pWind->DrawLine(WindWidth/2, YHalfDrawingArea - RestWidth/2, WindWidth/2, YHalfDrawingArea + RestWidth/2);
	pWind->DrawLine(WindWidth/2 - RestWidth/2, YHalfDrawingArea, WindWidth/2 + RestWidth/2, YHalfDrawingArea);
	//Light Circle;
	pWind->SetPen(GUIL, 3);
	pWind->SetBrush(GUIL);
	pWind->DrawCircle(600,275,50);

	// 5- Writing the letter of each region (A, B, C, D)
	pWind->SetPen(GUIR);
	pWind->SetFont(25, BOLD , BY_NAME, "Arial");
	pWind->DrawString(RestStartX + (int)(0.44*L), RestStartY + 5*L/12, "A");
	pWind->DrawString(RestStartX + (int)(0.44*L), YHalfDrawingArea + 5*L/12, "D");
	pWind->DrawString(WindWidth/2 + (int)(0.44*L), RestStartY + 5*L/12, "B");
	pWind->DrawString(WindWidth/2 + (int)(0.44*L), YHalfDrawingArea + 5*L/12, "C"); 

}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawSingleOrder(Order* pO, int RegionCount) const       // It is a private function
{

	if (RegionCount > MaxRegionOrderCount) 
		return; //no more orders can be drawn in this region

	int DrawDistance = RegionCount;
	int YPos = 1;
	if(RegionCount>=MaxHorizOrders )	//max no. of orders to draw in one line
	{
		DrawDistance = (RegionCount-1)%MaxHorizOrders + 1;
		YPos = (RegionCount-1) / MaxHorizOrders + 1; 
	}

	color clr = OrdersClrs[pO->GetType()];
	REGION Region = pO->GetRegion();

	int x, y, refX, refY;
	int shift = 27;
	//First calculate x,y position of the order on the output screen
	//It depends on the region and the order distance
	switch (Region)
	{
	case A_REG:
		refX = (WindWidth/2 - RestWidth/2);
		refY = YHalfDrawingArea - OrderHeight; //
		x = refX - DrawDistance*OrderWidth - DrawDistance; //(Distance)
		y = refY - YPos*OrderHeight - YPos; // YPos
		break;
	case B_REG:
		refX = (WindWidth/2 + RestWidth/2);
		refY = YHalfDrawingArea - OrderHeight; //
		x = refX + (DrawDistance-1)*OrderWidth + DrawDistance + shift; //(Distance)
		y = refY - YPos*OrderHeight - YPos; // YPos
		break;
	case C_REG:
		refX = (WindWidth/2 + RestWidth/2);
		refY = YHalfDrawingArea + OrderHeight; //
		x = refX + (DrawDistance-1)*OrderWidth + DrawDistance + shift; //(Distance)
		y = refY + (YPos-1)*OrderHeight + YPos; // YPos
		break;
	case D_REG:
		refX = (WindWidth/2 - RestWidth/2);
		refY = YHalfDrawingArea + OrderHeight; //
		x = refX - DrawDistance*OrderWidth - DrawDistance; //(Distance)
		y = refY + (YPos-1)*OrderHeight + YPos; // YPos
		break;
	default:
		break;
	}

	// Drawing the Order
	pWind->SetPen(clr);
	pWind->SetBrush(clr);
	//pWind->DrawRectangle(x, y, x + OrderWidth, y + OrderHeight);
	pWind->SetFont(20,BOLD, MODERN);
	pWind->DrawInteger(x,y,pO->GetID());
}


//////////////////////////////////////////////////////////////////////////////////////////
/* A function to draw a list of orders and ensure there is no overflow in the drawing*/
// To use this function, you must prepare its input parameters as specified
// [Input Parameters]:
//    orders [ ] : array of Order pointers (ALL orders from all regions in one array)
//    TotalOrders : the size of the array (total no. of orders)
void GUI::DrawOrders() const
{

	//Prepare counter for each region
	int RegionsCounts[REG_CNT]={0};	//initlaize all counters to zero

	for(int i=0; i<OrderCount; i++)
	{
		int orderRegion = OrdListForDrawing[i]->GetRegion();
		RegionsCounts[orderRegion]++;
		DrawSingleOrder(OrdListForDrawing[i], RegionsCounts[orderRegion]);
	}

}

void GUI::UpdateInterface() 
{
	ClearDrawingArea();
	DrawRestArea();
	DrawOrders();
	 ClearMenuBar() ;
}

/*
	AddOrderForDrawing: Adds a new order to the drawing list
*/
void GUI::AddOrderForDrawing(Order* ptr)
{
	if (OrderCount < MaxPossibleOrdCnt) 
		OrdListForDrawing[OrderCount++] = ptr;

	// Note that this function doesn't allocate any Order objects
	// It only makes the first free pointer in the array
	// points to the same Order pointed to by "ptr"
}

void GUI::ResetDrawingList()
{
	OrderCount = 0;		//resets the orders count to be ready for next timestep updates
}


PROG_MODE	GUI::getGUIMode() 
{
	PROG_MODE Mode;
	int x,y,S,s;
	CreateMenuBar();
	string Music;
	
	PrintMessage("Please select GUI mode From Menu");
	S=-1;
	
	while(S < 0 || S >= MODE_CNT)
	{
		pWind->WaitMouseClick(x, y);
		if (y >= 0 && y <= 50)
		S = x / MenuItemWidth;
		s = (WindWidth - x) / 120;
		if(s==0)
		{
			ChangeMode();
			UpdateInterface();
			CreateMenuBar();
			PrintMessage("Please select GUI mode From Menu");
			S = -1;
		}
		else if(s==1 && MusicOn)
		{
			PlaySound(NULL, NULL, 0); 
			MusicOn = false;
			UpdateInterface();
			CreateMenuBar();
			S = -1;
		}
		else if(s == 1 && !MusicOn)
		{
			Music = GetFileName("WAV");
			replace(Music.begin(), Music.end(), '\\', '/');
			fstream fin;
			fin.open(Music);
			if(fin.is_open())
			{
				PlaySound((LPCSTR)Music.c_str(), NULL, SND_ASYNC | SND_LOOP | SND_NODEFAULT);
				MusicOn = true;
				UpdateInterface();
				CreateMenuBar();
				S = - 1;
			}
			fin.close();
		}

		
	}
	//while(Mode> 0 || Mode >= MODE_CNT);
	Mode = (PROG_MODE) (S);
	UpdateInterface();
	return Mode;
}

void GUI::ResetDrawNumbers()
{

	for(int i=A_REG;i<REG_CNT;i++)
	{

		NumberOfVIPOrders[i]=0;        
		NumberOfNormalOrders[i]=0;
		NumberOfFrozenOrders[i]=0;

	}

}

string GUI::GetFileName(string mode)
{
	string s = pWind->open_file(mode);
	SetCurrentDirectory(oldDir);
	return s;
}
string GUI::SaveFileName()
{
	string s = pWind->save_file();
	SetCurrentDirectory(oldDir);
	return s;
}