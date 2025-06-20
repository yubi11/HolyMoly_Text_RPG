#include "Shop.h"

#include "HealthPotion.h"
#include "AttackBoost.h"

#include "Character.h"

enum class ESelectMenu
{
	Buy = 1,	// 1
	Sell,		// 2
	END = 999
};

enum class ESelectBuyItem
{
	HealthPotion = 1,	// 1
	AttackBoost,		// 2
	END = 999
};

enum class EItem
{
	HealthPotion,		// 0
	AttackBoost,		// 1
	END = 999
};

Shop::Shop()
{
	availableItems.push_back(make_unique<HealthPotion>());
	availableItems.push_back(make_unique<AttackBoost>());
}

void Shop::OnEnter(Character* player)
{
	//==========================================
	// 출력 - 아스키아트(Welcome)
	//==========================================
	// 아스키아트 - Welcome
	vector<string> vecAsciiArt_Welcome;
	vecAsciiArt_Welcome = {
		"  _    _        _                                ",
		" | |  | |      | |                               ",
		" | |  | |  ___ | |  ___   ___   _ __ ___    ___  ",
		" | |/\\| | / _ \\| | / __| / _ \\ | '_ ` _ \\  / _ \\ ",
		" \\  /\\  /|  __/| || (__ | (_) || | | | | ||  __/ ",
		"  \\/  \\/  \\___||_| \\___| \\___/ |_| |_| |_| \\___| "
	};

	for (size_t i = 0; i < vecAsciiArt_Welcome.size(); ++i)
	{
		FnSetTextColor(EColors::LIGHT_RED);
		cout << vecAsciiArt_Welcome[i] << endl;
		FnSleep(100);
	}
	cout << endl;

	//==========================================
	// 출력 - 환영인사
	//==========================================
	// 텍스트 컬러 변경
	FnSetTextColor(EColors::YELLOW);
	string str_Welcome = "상점에 오신 것을 환영합니다!\n";
	for (int i = 0; i < str_Welcome.length(); i++)
	{
		cout << str_Welcome[i];
		FnSleep(10);
	}
	// 텍스트 컬러 기본색 복구
	FnSetTextDefault();

	//==========================================
	// 입력(선택값) - 구매 or 판매
	//==========================================
	// 텍스트 컬러 변경
	FnSetTextColor(EColors::YELLOW);
	string strAsk = "원하는 메뉴를 선택하세요.\n";
	for (char ch : strAsk)
	{
		cout << ch;
		FnSleep(10);
	}
	// 텍스트 컬러 기본색 복구
	FnSetTextDefault();

	// 텍스트 컬러 변경
	FnSetTextColor(EColors::LIGHT_YELLOW);
	cout << "[1] ";
	FnSetTextColor(EColors::YELLOW);
	cout << "아이템 구매\n";
	FnSetTextColor(EColors::LIGHT_YELLOW);
	cout << "[2] ";
	FnSetTextColor(EColors::YELLOW);
	cout << "아이템 판매\n";

	// 텍스트 컬러 기본색 복구
	FnSetTextDefault();

	//------------------------
	// 입력
	//------------------------
	string input_SelectMenu = "";
	while (true)
	{
		cout << "입력: ";
		//cin.ignore();
		getline(std::cin, input_SelectMenu);

		if (input_SelectMenu.empty())
		{
			FnSetTextColor(EColors::LIGHT_RED);
			std::cout << "입력값은 비워둘 수 없습니다." << endl;
			FnSetTextDefault();
			continue;
		}
		if (input_SelectMenu.find(' ') != std::string::npos)
		{
			FnSetTextColor(EColors::LIGHT_RED);
			std::cout << "입력값은 공백을 포함할 수 없습니다." << endl;
			FnSetTextDefault();
			continue;
		}

		bool isOk = false;
		if (FnIsNumber(input_SelectMenu))
		{// 입력값이 숫자인 경우
			int digit = stoi(input_SelectMenu);
			if ((ESelectMenu::Buy == static_cast<ESelectMenu>(digit))
				|| (ESelectMenu::Sell == static_cast<ESelectMenu>(digit)))
			{
				isOk = true;
				break;
			}
		}

		if (!isOk)
		{// 입력값이 영문인 경우, 숫자여도 유효한 값이 아닌 경우
			FnSetTextColor(EColors::LIGHT_RED);
			std::cout << "유효한 입력값이 아닙니다." << endl;
			FnSetTextDefault();
			continue;
		}
	}
	cout << endl;

	//==========================================
	// 분기 - 구매 or 판매
	//==========================================
	ESelectMenu result = static_cast<ESelectMenu>(stoi(input_SelectMenu));
	switch (result)
	{
	case ESelectMenu::Buy:
		BuyItem(player);
		break;
	case ESelectMenu::Sell:
		SellItem(player);
		break;
	case ESelectMenu::END:
		break;
	default:
		break;
	}
}//END-void Shop::OnEnter

void Shop::DisplayItems(Character* player)
{
	//==========================================
	// 출력 - 아이템 목록 출력 전처리
	//==========================================
	FnSetTextColor(EColors::LIGHT_GREEN);
	cout << "==============================================\n";
	string str_ShowItemListBefore = "구매 가능한 아이템:\n";
	for (char ch : str_ShowItemListBefore)
	{
		cout << ch;
		FnSleep(10);
	}
	// 텍스트 컬러 기본색 복구
	FnSetTextDefault();

	//==========================================
	// 문장 조립 - 아이템 목록
	//==========================================
	string str_ItemList = "";
	//for (const Item* item : availableItems)
	for (const std::unique_ptr<Item>& itemPtr : availableItems)
	{
		str_ItemList += itemPtr->getName();
		str_ItemList += " (";

		string strItemName = itemPtr->getName();
		if (strItemName.find("Health") != string::npos)
		{
			str_ItemList += "체력";
		}
		else if (strItemName.find("Attack") != string::npos)
		{
			str_ItemList += "공격력";
		}
		else
		{
			str_ItemList += "error";
		}

		str_ItemList += " +";
		str_ItemList += to_string(itemPtr->getIncreseAmount());
		str_ItemList += "): ";
		str_ItemList += to_string(itemPtr->getPrice());
		str_ItemList += " 골드";
		str_ItemList += ",";
	}

	// 문장 마지막에 들어간 쉼표(구분자) 제거
	str_ItemList.pop_back();

	//==========================================
	// 출력 - 아이템 목록
	//==========================================
	stringstream ss(str_ItemList);
	string token;

	int idx_ItemList = 1;
	while (getline(ss, token, ','))
	{
		// 텍스트 컬러 변경
		FnSetTextColor(EColors::LIGHT_YELLOW);
		cout << "[" << idx_ItemList++ << "] ";

		// 텍스트 컬러 변경
		FnSetTextColor(EColors::YELLOW);
		cout << token << endl;
	}

	//==========================================
	// 출력 - 아이템 목록 출력 후처리
	//==========================================
	FnSetTextColor(EColors::LIGHT_GREEN);
	cout << "==============================================\n";
	// 텍스트 컬러 기본색 복구
	FnSetTextDefault();
}//END - void Shop::DisplayItems;

void Shop::BuyItem(Character* player)
{
	//==========================================
	// 출력 - 아스키아트(PurcahseMode)
	//==========================================
	// 아스키아트 - PurcahseMode
	vector<string> vecAsciiArt_Purchase;
	vecAsciiArt_Purchase = {
		"______                     _                        ___  ___            _                 ",
		"| ___ \\                   | |                       |  \\/  |           | |              ",
		"| |_/ / _   _  _ __   ___ | |__    __ _  ___   ___  | .  . |  ___    __| |  ___           ",
		"|  __/ | | | || '__| / __|| '_ \\  / _` |/ __| / _ \\ | |\\/| | / _ \\  / _` | / _ \\     ",
		"| |    | |_| || |   | (__ | | | || (_| |\\__ \\|  __/ | |  | || (_) || (_| ||  __/        ",
		"\\_|     \\__,_||_|    \\___||_| |_| \\__,_||___/ \\___| \\_|  |_/ \\___/  \\__,_| \\___|  "
	};
	for (size_t i = 0; i < vecAsciiArt_Purchase.size(); ++i)
	{
		FnSetTextColor(EColors::LIGHT_GREEN);
		cout << vecAsciiArt_Purchase[i] << endl;
		FnSleep(100);
	}
	cout << endl;
	// 텍스트 컬러 기본색 복구
	FnSetTextDefault();

	//==========================================
	// 출력 - 아이템 목록
	//==========================================
	DisplayItems(player);

	//==========================================
	// 입력 - 구매할 아이템 번호 선택
	//==========================================
	// 텍스트 컬러 변경
	FnSetTextColor(EColors::YELLOW);
	string strAsk = "구매할 아이템 번호를 선택하세요.\n";
	for (int i = 0; i < strAsk.length(); i++)
	{
		cout << strAsk[i];
		FnSleep(10);
	}
	// 텍스트 컬러 기본색 복구
	FnSetTextDefault();

	//------------------------
	// 입력
	//------------------------
	string input_SelectBuyItem = "";
	while (true)
	{
		cout << "입력: ";
		//cin.ignore();
		getline(std::cin, input_SelectBuyItem);

		if (input_SelectBuyItem.empty())
		{
			FnSetTextColor(EColors::LIGHT_RED);
			std::cout << "입력값은 비워둘 수 없습니다." << endl;
			FnSetTextDefault();
			continue;
		}
		if (input_SelectBuyItem.find(' ') != std::string::npos)
		{
			FnSetTextColor(EColors::LIGHT_RED);
			std::cout << "입력값은 공백을 포함할 수 없습니다." << endl;
			FnSetTextDefault();
			continue;
		}

		bool isOk = false;
		if (FnIsNumber(input_SelectBuyItem))
		{// 입력값이 숫자인 경우
			int digit = stoi(input_SelectBuyItem);
			if ((ESelectBuyItem::HealthPotion == static_cast<ESelectBuyItem>(digit))
				|| (ESelectBuyItem::AttackBoost == static_cast<ESelectBuyItem>(digit)))
			{
				isOk = true;
				break;
			}
		}

		if (!isOk)
		{// 입력값이 영문인 경우, 숫자여도 유효한 값이 아닌 경우
			FnSetTextColor(EColors::LIGHT_RED);
			std::cout << "유효한 입력값이 아닙니다." << endl;
			FnSetTextDefault();
			continue;
		}
	}
	cout << endl;

	//==========================================
	// 분기 - 구매 or 판매
	//==========================================
	string name = "";
	ESelectBuyItem result = static_cast<ESelectBuyItem>(stoi(input_SelectBuyItem));
	switch (result)
	{
	case ESelectBuyItem::HealthPotion:
	{
		name = availableItems[static_cast<int>(EItem::HealthPotion)]->getName();
	}
	break;
	case ESelectBuyItem::AttackBoost:
	{
		name = availableItems[static_cast<int>(EItem::AttackBoost)]->getName();
	}
	break;
	case ESelectBuyItem::END:
		break;
	default:
		break;
	}

	// 구매 처리
	player->addItem(name, 1);

}//END-void Shop::BuyItem

void Shop::SellItem(Character* player)
{
	//==========================================
	// 출력 - 아스키아트(SalesMode)
	//==========================================
	// 아스키아트 - SalesMode
	vector<string> vecAsciiArt_Sales;
	vecAsciiArt_Sales = {
		" _____         _            ___  ___            _        ",
		"/  ___|       | |           |  \\/  |           | |       ",
		"\\ `--.   __ _ | |  ___  ___ | .  . |  ___    __| |  ___  ",
		" `--. \\ / _` || | / _ \\/ __|| |\\/| | / _ \\  / _` | / _ \\ ",
		"/\\__/ /| (_| || ||  __/\\__ \\| |  | || (_) || (_| ||  __/ ",
		"\\____/  \\__,_||_| \\___||___/\\_|  |_/ \\___/  \\__,_| \\___| "
	};
	for (size_t i = 0; i < vecAsciiArt_Sales.size(); ++i)
	{
		FnSetTextColor(EColors::LIGHT_BLUE);
		cout << vecAsciiArt_Sales[i] << endl;
		FnSleep(100);
	}
	cout << endl;
	// 텍스트 컬러 기본색 복구
	FnSetTextDefault();
}//END-void Shop::SellItem
