#include "GUI.h"

//////////////////////////////////////////////////////////////////////////////////////////
GUI::GUI()
{
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

void GUI::PrintMessage(string msg, string line1, string line2, string line3, string line4) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(WHITE);
	pWind->SetFont(18, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(10, WindHeight - (int) (StatusBarHeight/1.06), msg); // You may need to change these coordinates later 
	pWind->DrawString(12, WindHeight - (int) (StatusBarHeight/1.28), line1); //second line
	pWind->DrawString(10, WindHeight - (int) (StatusBarHeight/1.65), line2); //third line
	pWind->DrawString(10, WindHeight - (int) (StatusBarHeight/2.4), line3); //fourth line 
	pWind->DrawString(10, WindHeight - (int) (StatusBarHeight/4), line4);

}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::PrintTime(string t, color clr) const	//Prints a message on status bar
{
	
	
	pWind->SetPen(clr);
	pWind->SetFont(32, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(565, 260, t); // You may need to change these coordinates later 
	
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
	pWind->SetPen(DARKGUID, 3);
	pWind->SetBrush(DARKGUID);
	pWind->DrawRectangle(0, 0, WindWidth, MenuBarHeight);	

		
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateMenuBar()
{
	string MenuItemImages[MENU_COUNT];
	MenuItemImages[INTERACTIVE] = "images\\interactive.jpg";
	MenuItemImages[STEPBYSTEP] = "images\\steps.jpg";
	MenuItemImages[SILENT] = "images\\silent.jpg";
	MenuItemImages[TEST] = "images\\test.jpg";
	for(int i=0; i<MENU_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*MenuItemWidth, 0, MenuItemWidth, 50);
	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(0, MenuBarHeight , WindWidth,MenuBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusBar() const
{
	pWind->SetPen(DARKGUID, 3);
	pWind->SetBrush(DARKGUID);
	pWind->DrawRectangle(0, WindHeight - StatusBarHeight , WindWidth, WindHeight);	

	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(0, WindHeight - StatusBarHeight , WindWidth, WindHeight - StatusBarHeight);	
}
///////////////////////////////////////////////////////////////////////////////////
void GUI::ClearDrawingArea() const
{
	// Clearing the Drawing area
	pWind->SetPen(DARKGUIL, 3);
	pWind->SetBrush(DARKGUIL);
	pWind->DrawRectangle(0, MenuBarHeight, WindWidth, WindHeight - StatusBarHeight);
}
///////////////////////////////////////////////////////////////////////////////////
void GUI::DrawRestArea() const
{
	int L = RestWidth / 2;

	// 1- Drawing the brown square of the Rest
	pWind->SetPen(DARKGUID);
	pWind->SetBrush(DARKGUID);
	//Dark Circle;
	pWind->DrawCircle(600,275,120);

	// 2- Drawing the 2 brown crossed lines (for making 4 regions)
	pWind->SetPen(DARKGUID, 5);
	pWind->DrawLine(0, YHalfDrawingArea, WindWidth, YHalfDrawingArea);
	pWind->DrawLine(WindWidth/2, MenuBarHeight, WindWidth/2, WindHeight-StatusBarHeight);

	// 3- Drawing the 2 white crossed lines (inside the Rest)
	pWind->SetPen(DARKGUID,5);
	pWind->DrawLine(WindWidth/2, YHalfDrawingArea - RestWidth/2, WindWidth/2, YHalfDrawingArea + RestWidth/2);
	pWind->DrawLine(WindWidth/2 - RestWidth/2, YHalfDrawingArea, WindWidth/2 + RestWidth/2, YHalfDrawingArea);
	//Light Circle;
	pWind->SetPen(DARKGUIL, 3);
	pWind->SetBrush(DARKGUIL);
	pWind->DrawCircle(600,275,50);
	/*
	// 4- Drawing the 4 white squares inside the Rest (one for each tower)
	pWind->SetPen(WHITE);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(RestStartX + L/3, RestStartY + L/3, RestStartX + 2*L/3, RestStartY + 2*L/3);
	pWind->DrawRectangle(RestStartX + L/3, RestEndY - L/3, RestStartX + 2*L/3, RestEndY - 2*L/3);
	pWind->DrawRectangle(RestEndX - 2*L/3, RestStartY + L/3, RestEndX - L/3, RestStartY + 2*L/3);
	pWind->DrawRectangle(RestEndX - 2*L/3, RestEndY - L/3, RestEndX - L/3, RestEndY - 2*L/3);
	*/
	// 5- Writing the letter of each region (A, B, C, D)
	pWind->SetPen(WHITE);
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
		x = refX + (DrawDistance-1)*OrderWidth + DrawDistance; //(Distance)
		y = refY - YPos*OrderHeight - YPos; // YPos
		break;
	case C_REG:
		refX = (WindWidth/2 + RestWidth/2);
		refY = YHalfDrawingArea + OrderHeight; //
		x = refX + (DrawDistance-1)*OrderWidth + DrawDistance; //(Distance)
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
	CountNumbersOfRegions();
	ClearDrawingArea();
	DrawRestArea();
	DrawOrders();
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


PROG_MODE	GUI::getGUIMode() const
{
	PROG_MODE Mode;
	int x,y,S;
	PrintMessage("Please select GUI mode From Menu");
	S=-1;
	
	while(S<0||S>MODE_CNT)
	{
		pWind->WaitMouseClick(x, y);
		if (y >= 0 && y <= 50)
		S = x /MenuItemWidth;
		
	}
	//while(Mode> 0 || Mode >= MODE_CNT);
	Mode = (PROG_MODE) (S);
	return Mode;
}

void GUI::CountNumbersOfRegions() 
{
	Order*O;
	for (int i=0;i<OrderCount;i++)
		{
			O=OrdListForDrawing[i];
			if (O->GetRegion() == A_REG)
				{
					if(O->GetType() == TYPE_VIP )
						{
							NumberOfVIPOrders[A_REG]++;continue;
						}
					if(O->GetType() == TYPE_NRM )
						{
							NumberOfNormalOrders[A_REG]++;continue;
						}
					if(O->GetType() == TYPE_FROZ )
						{
							NumberOfFrozenOrders[A_REG]++;continue;
						}
				}

			if (O->GetRegion() == B_REG)
				{
					if(O->GetType() == TYPE_VIP )
						{
							NumberOfVIPOrders[B_REG]++;continue;
						}
					if(O->GetType() == TYPE_NRM )
						{
							NumberOfNormalOrders[B_REG]++;continue;
						}
					if(O->GetType() == TYPE_FROZ )
						{
							NumberOfFrozenOrders[B_REG]++;continue;
						}
				}

			if (O->GetRegion() == C_REG)
				{
					if(O->GetType() == TYPE_VIP )
						{
							NumberOfVIPOrders[C_REG]++;continue;
						}
					if(O->GetType() == TYPE_NRM )
						{
							NumberOfNormalOrders[C_REG]++;continue;
						}
					if(O->GetType() == TYPE_FROZ )
						{
							NumberOfFrozenOrders[C_REG]++;continue;
						}
				}

			if (O->GetRegion() == D_REG)
				{
					if(O->GetType() == TYPE_VIP )
						{
							NumberOfVIPOrders[D_REG]++;continue;
						}
					if(O->GetType() == TYPE_NRM )
						{
							NumberOfNormalOrders[D_REG]++;continue;
						}
					if(O->GetType() == TYPE_FROZ )
						{
							NumberOfFrozenOrders[D_REG]++;continue;
						}
				}

		}	

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