#include "Shop.h"

enum class EMenu
{
	Main,		// 0
	Buy,		// 1
	Sell,		// 2
	Exit,		// 3
	END
};

enum class EYesNo
{
	Yes = 1,	// 1
	No,			// 2
	END
};

Shop::Shop(Character* player, bool _isSpecial)
	:mIsFirstEntry(true), mSaleRatio(0.6f), mIsSpecialShop(_isSpecial)
{
	//==========================================
	// �Ǹ� ���� ������ ��� ����
	//==========================================
	if (!mIsSpecialShop)
	{// �Ϲ� ����
		int size = static_cast<int>(EItemRegular::END);
		for (int i = 0; i < size; i++)
		{
			EItemRegular key = static_cast<EItemRegular>(i);
			switch (key)
			{
			case EItemRegular::HealthPotion:
				mCatalog_Reugular[key] = std::make_unique<HealthPotion>();
				break;
			case EItemRegular::AttackBoost:
				mCatalog_Reugular[key] = std::make_unique<AttackBoost>();
				break;
			case EItemRegular::ExpBook:
				mCatalog_Reugular[key] = std::make_unique<ExpBook>();
				break;
			case EItemRegular::GoldBar:
				mCatalog_Reugular[key] = std::make_unique<GoldBar>();
				break;
			case EItemRegular::rottenMeat:
				mCatalog_Reugular[key] = std::make_unique<rottenMeat>();
				break;
			case EItemRegular::END:
				break;
			default:
				break;
			}
		}
	}
	else
	{// Ư�� ����
		int size = static_cast<int>(EItemSpecial::END);
		for (int i = 0; i < size; i++)
		{
			EItemSpecial key = static_cast<EItemSpecial>(i);
			switch (key)
			{
			case EItemSpecial::HolyWater:
				mCatalog_Special[key] = std::make_unique<HolyWater>();
				break;
			case EItemSpecial::Bomb:
				mCatalog_Special[key] = std::make_unique<Bomb>();
				break;
			case EItemSpecial::END:
				break;
			default:
				break;
			}
		}
	}

	// �α� �޽��� �ʱ�ȭ
	CreateLog();

	// ���� ����
	OnEnter(player);
}

void Shop::OnEnter(Character* player)
{
	//==========================================
	// ��� - �ƽ�Ű��Ʈ Only ��������
	//==========================================
	// �ƽ�Ű��Ʈ
	vector<string> vecAsciiArt_Welcome;

	if (!mIsSpecialShop)
	{
		// ��� - �ƽ�Ű��Ʈ
		vecAsciiArt_Welcome = {
				"  _    _        _                                           ",
				" | |  | |      | |                                          ",
				" | |  | |  ___ | |  ___   ___   _ __ ___    ___             ",
				" | |/\\| | / _ \\| | / __| / _ \\ | '_ ` _ \\  / _ \\       ",
				" \\  /\\  /|  __/| || (__ | (_) || | | | | ||  __/          ",
				"  \\/  \\/  \\___||_| \\___| \\___/ |_| |_| |_| \\___|      ",
				"                                                            "

		};
		PrintByLineWithColor(vecAsciiArt_Welcome, EColors::LIGHT_CYAN, ETypingSpeed::FAST);
		cout << endl;

		// ��� - ȯ���λ�
		const string str_Welcome = "������ ���� ���� ȯ���մϴ�!\n�������� �����ϰų� �Ǹ��� ������!\n\n\n";
		PrintBySpellingWithColor(str_Welcome, EColors::YELLOW, ETypingSpeed::FAST);
	}
	else
	{
		vecAsciiArt_Welcome = {
		"               (       \"     )                                  ",
		"                ( _  *                                          ",
		"                   * (     /      \\    ___                      ",
		"                      \"     \"        _/ /                       ",
		"                     (   *  )    ___/   |                       ",
		"                       )   \"     _ o)'-./__                     ",
		"                      *  _ )    (_, . $$$                       ",
		"                      (  )   __ __ 7_ $$$$                      ",
		"                       ( :  { _)  '---  $\\                      ",
		"                  ______'___//__\\   ____, \\                     ",
		"                   )           ( \\_/ _____\\_                    ",
		"                 .'             \\   \\------''.                  ",
		"                 |='           '=|  |         )                 ",
		"                 |               |  |  .    _/                  ",
		"                  \\    (. ) ,   /  /__I_____\\                   ",
		"                   '._/_)_(\\__.'   (__,(__,_]                   ",
		"                  @---()_.'---@                                 "
		};
		// �÷� ����
		vector<int> colors = {
			static_cast<int>(EColors::GREEN),
			static_cast<int>(EColors::RED),
			static_cast<int>(EColors::LIGHT_CYAN),
			static_cast<int>(EColors::LIGHT_BLUE),
			static_cast<int>(EColors::YELLOW)
		};
		// ��� - �ƽ�Ű��Ʈ
		for (size_t i = 0; i < vecAsciiArt_Welcome.size(); ++i)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colors[i % colors.size()]);
			cout << vecAsciiArt_Welcome[i] << endl;;
		}
		cout << endl;

		// ��� - ȯ���λ�
		const string str_Welcome = "��������l ���� ���� ȯ����LI����!\n��r��l���� ���ଫ�̪Ĥä�r �ǡଫ���� ���ѤĿ�!\n\n\n";
		PrintBySpellingWithColor(str_Welcome, EColors::YELLOW, ETypingSpeed::FAST);
	}

	//==========================================
	// ���� �޴�
	//==========================================
	MainMenu(player);
}//END-void Shop::OnEnter

bool Shop::OnExit(Character* player)
{
	bool returnValue = false;
	//==========================================
	// ��� - �ŷ� �α�
	//==========================================
	system("cls"); // ȭ�� �����
	PrintLog();

	//==========================================
	// ��� - �ƽ�Ű��Ʈ(Caution)
	//==========================================
	PrintAsciiArt(static_cast<int>(EMenu::Exit));

	// ��� - ���� ������ ������
	string str = "";
	if (!mIsSpecialShop)
	{// �Ϲ� ����
		str = "�̰��� ����� �ٷ� ������ ���۵˴ϴ�.\n���� �����ðڽ��ϱ�?\n";
	}
	else
	{// Ư�� ����
		str = "��l���� ��������r�� ���÷� ������r ���۵�LI����\n���� ��r��r�󩥰ڽ�LI��?\n";
	}
	PrintBySpellingWithColor(str, EColors::RED, ETypingSpeed::FAST);

	// ���� - ���� ������
	if (IsYes(player))
	{
		returnValue = true;
	}

	FnSetTextDefault();
	return returnValue;
}//END-void Shop::OnExit

void Shop::DisplayItems(Character* player)
{
	// Ư�� ���� - �ƽ�Ű��Ʈ ���� ��¿�
	vector<int> colors = {
		static_cast<int>(EColors::GREEN),
		static_cast<int>(EColors::RED),
		static_cast<int>(EColors::LIGHT_CYAN),
		static_cast<int>(EColors::LIGHT_BLUE),
		static_cast<int>(EColors::YELLOW)
	};
	string strLine = "�ߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡߡ�\n";

	//==========================================
	// ��� - ������ ��� ��� ��ó��
	//==========================================
	const string str_Catalog = "�Ǹ� ���� ������ ���:\n";
	const string str_Catalog2 = "�ǡଫ ���� ��r��l�� ���:\n";
	if (!mIsSpecialShop)
	{// �Ϲ� ����
		// ��� - ����
		FnSetTextColor(EColors::LIGHT_GREEN);
		cout << "======================================================================================\n";
		// ��� - ����
		PrintBySpellingWithColor(str_Catalog, EColors::LIGHT_GREEN, ETypingSpeed::FAST);
	}
	else
	{// Ư�� ����
		// ��� - ����
		for (size_t i = 0; i < strLine.size(); ++i)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colors[(i + 3) % colors.size()]);
			cout << strLine[i];
		}
		// ��� - ����
		PrintBySpellingWithColor(str_Catalog2, EColors::LIGHT_GREEN, ETypingSpeed::FAST);
	}

	//==========================================
	// ��� - ������ ���
	//==========================================
	string str_effect;
	string strPrint;
	int idx = 1;
	if (!mIsSpecialShop)
	{// �Ϲ� ����
		for (const pair<const EItemRegular, unique_ptr<Item>>& pair : mCatalog_Reugular)
		{
			const EItemRegular& key = pair.first;			// ������ Ű (EItemRegular Ÿ��)
			const unique_ptr<Item>& itemPtr = pair.second;	// ������ ������

			const int price = itemPtr->getPrice();			// ������ ����
			const int playerGold = player->getGold();		// �÷��̾� ���� ���

			if (price > playerGold)
			{// ��Ȱ��ȭ : ���� ���� ���� ���δ� ������ �� ���� ���
				FnSetTextColor(EColors::DARK_GRAY);
				cout << "[" << idx++ << "] ";
			}
			else
			{// Ȱ��ȭ : ��尡 ����ؼ� ������ �� �ִ� ���
				// �ε����� ����, ����ڰ� ��ȣ �Է��� �� ��, ������ �ε����� �ð��� ������ �־� ������ ���ϵ��� ��
				FnSetTextColor(EColors::LIGHT_YELLOW);
				cout << "[" << idx++ << "] ";

				FnSetTextColor(EColors::YELLOW);
			}

			switch (key)
			{
			case EItemRegular::HealthPotion:	str_effect = "HP"; break;
			case EItemRegular::AttackBoost:		str_effect = "ATK"; break;
			case EItemRegular::ExpBook:			str_effect = "EXP"; break;
			case EItemRegular::GoldBar:			str_effect = "GOLD"; break;
			case EItemRegular::rottenMeat:		str_effect = "HP"; break;
			case EItemRegular::END: break;
			default: break;
			}

			// ��� - ������ �̸� + ȿ�� + ����
			strPrint = itemPtr->getName() + " (" + str_effect + " +" + to_string(itemPtr->getItemValue()) + ")";
			cout << left << setw(38) << strPrint			// �̸� + ȿ�� (38ĭ)
				<< ": " << right << setw(3) << price		// ���� (3ĭ)
				<< "(G)" << endl;
		}
	}
	else
	{// Ư�� ����
		for (const pair<const EItemSpecial, unique_ptr<Item>>& pair : mCatalog_Special)
		{
			const EItemSpecial& key = pair.first;			// ������ Ű (EItemSpecial Ÿ��)
			const unique_ptr<Item>& itemPtr = pair.second;  // ������ ������

			const int price = itemPtr->getPrice();			// ������ ����
			const int playerGold = player->getGold();		// �÷��̾� ���� ���

			if (price > playerGold)
			{// ��Ȱ��ȭ : ���� ���� ���� ���δ� ������ �� ���� ���
				FnSetTextColor(EColors::DARK_GRAY);
				cout << "[" << idx++ << "] ";
			}
			else
			{// Ȱ��ȭ : ��尡 ����ؼ� ������ �� �ִ� ���
				// �ε����� ����, ����ڰ� ��ȣ �Է��� �� ��, ������ �ε����� �ð��� ������ �־� ������ ���ϵ��� ��
				FnSetTextColor(EColors::LIGHT_YELLOW);
				cout << "[" << idx++ << "] ";

				FnSetTextColor(EColors::YELLOW);
			}

			switch (key)
			{
			case EItemSpecial::HolyWater:	str_effect = "HP"; break;
			case EItemSpecial::Bomb:		str_effect = "ATK"; break;
			case EItemSpecial::END: break;
			default: break;
			}

			// ��� - ������ �̸� + ȿ�� + ����
			strPrint = itemPtr->getName() + " (" + str_effect + " +" + to_string(itemPtr->getItemValue()) + ")";
			cout << left << setw(38) << strPrint			// �̸� + ȿ�� (38ĭ)
				<< ": " << right << setw(3) << price		// ���� (3ĭ)
				<< "(G)" << endl;
		}
	}
	//==========================================
	// ��� - ������ ��� ��� ��ó��
	//==========================================
	if (!mIsSpecialShop)
	{// �Ϲ� ����
		// ��� - ����
		FnSetTextColor(EColors::LIGHT_GREEN);
		cout << "======================================================================================\n";
	}
	else
	{// Ư�� ����
		// ��� - ����
		for (size_t i = 0; i < strLine.size(); ++i)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colors[(i + 3) % colors.size()]);
			cout << strLine[i];
		}
	}

	FnSetTextDefault();
}//END - void Shop::DisplayItems;

void Shop::BuyItem(Character* player)
{
	bool isContinue = true;
	while (isContinue)
	{
		//==========================================
		// ��� - �ŷ� �α�
		//==========================================
		system("cls"); // ȭ�� �����
		PrintLog();

		//==========================================
		// ��� - �ƽ�Ű��Ʈ(Purcahse)
		//==========================================
		PrintAsciiArt(static_cast<int>(EMenu::Buy));

		// ��� - ���� ������ ������	
		if (!mIsSpecialShop)
		{// �Ϲ� ����
			FnSetTextColor(EColors::LIGHT_YELLOW);	cout << "[0] �������� ���ư���\n";
		}
		else
		{// Ư�� ����
			FnSetTextColor(EColors::LIGHT_YELLOW);	cout << "[0] ��l������ ����r��r��l\n";
		}

		// ��� - ������ ���
		DisplayItems(player);

		//==========================================
		// ���� ���ɼ� Ȯ��
		//==========================================
		/*
			�÷��̾� ���� �ݾ���
			��ǰ ���� �� �ּ� ���ݺ��� ������
			�������� ������ �� ����
			���� �޴��� ���ư��� �������� �����Ѵ�.
		*/
		//==========================================
		// ���� �Ұ� (��� < ������)
		//==========================================
		if (!IsEnoughGoldBuyLowestPrice(player))
		{
			PrintPurchaseNotPossible(player, false);

			//==========================================
			// ȸ�� - ���� �޴�
			//==========================================
			isContinue = false; continue;
		}

		//==========================================
		// ���� ���� (��� >= ������)
		//==========================================
		// ��� - �÷��̾� �κ��丮 ������ ���� �б�
		if (!player->getInventory().empty())
		{// �κ��丮�� ��� ���� ���� ���
			if (!mIsSpecialShop)
			{// �Ϲ� ����
				DisplayPlayerInventory<EItemRegular>(player, false);
			}
			else
			{// Ư�� ����
				DisplayPlayerInventory<EItemSpecial>(player, false);
			}
		}
		else
		{// �κ��丮�� ��� �ִ� ���
			PrintEmptyInventoryMessage();
		}

		// ��� - �÷��̾� ���� �ݾ�
		PrintPlayerGold(player, true);

		// ���� - ������ ������
		string strAsk_SelectItem = "";
		if (!mIsSpecialShop)
		{// �Ϲ� ����
			strAsk_SelectItem += "\"�Ǹ� ���� ������ ���\"����, �����Ϸ��� ������ ��ȣ�� �ϳ��� �����ϼ���.\n";
			strAsk_SelectItem += "���� �޴��� ���ư����� ���� 0���� �����ϼ���.\n";
		}
		else
		{// Ư�� ����
			strAsk_SelectItem += "\"�ǡଫ ���� ��r��l�� ���\"����ln��, ���ଫ�̷��� ��r��l�� ��ȣ�� �̤�rϢ�� ���é̫ѤĿ�.\n";
			strAsk_SelectItem += "��l�� �޴��� ����r��r���� ������ 0���� ���é̫ѤĿ�.\n";
		}
		PrintBySpellingWithColor(strAsk_SelectItem, EColors::YELLOW, ETypingSpeed::FAST);

		//==========================================
		// �Է�(1) - ������ ��ȣ
		//==========================================
		int selection = -1;
		if (!mIsSpecialShop)
		{// �Ϲ� ����
			selection = stoi(CheckInputValidation(0, mCatalog_Special.size(), player, true));
		}
		else
		{// Ư�� ����
			selection = stoi(CheckInputValidation(0, mCatalog_Special.size(), player, true));
		}

		// �������� ���ư��⸦ ������ ���
		const int EXIT = 0;
		if (EXIT == selection)
		{
			//==========================================
			// ȸ�� - ���� �޴�
			//==========================================
			isContinue = false; continue;
		}

		//==========================================
		// ���� ���ɼ� Ȯ�� (��� < ���� ������ ����)
		//==========================================
		const int key_digit = selection - 1; // ȭ��� ���ù�ȣ�� 1�������̹Ƿ� -1 ó����.
		int price = 0;

		if (!mIsSpecialShop)
		{// �Ϲ� ����
			price = mCatalog_Reugular[static_cast<EItemRegular>(key_digit)]->getPrice();
		}
		else
		{// Ư�� ����
			price = mCatalog_Special[static_cast<EItemSpecial>(key_digit)]->getPrice();
		}

		if (price > player->getGold())
		{// ���� �Ұ�
			PrintPurchaseNotPossible(player, false);

			//==========================================
			// ȸ�� - ���� �޴�
			//==========================================
			isContinue = false; continue;
		}

		//==========================================
		// ���� ���� (��� >= ���� ������ ����)
		//==========================================
		// ���� ������ �ִ� ���� ã�� (���� ��差 / ������ ���� = ���� ������ �ִ� ����)
		int quantity_possibleMAX = player->getGold() / price;

		//==========================================
		// �Է�(2) - ����
		//==========================================
		int digit_Quantity = 0; // ������ ������ ����
		const int ONE = 1;

		// ���� ���� - ������ ���� �Է� �ȳ�
		string strAsk_HowMany = "";
		if (!mIsSpecialShop)
		{// �Ϲ� ����
			strAsk_HowMany += "������ �������� ���� ���� ���� �ִ� ";
		}
		else
		{// Ư�� ����
			strAsk_HowMany += "���ä��� ��r��l���� �ҫ�l ���� ���� �֤��� ";
		}
		PrintBySpellingWithColor(strAsk_HowMany, EColors::YELLOW, ETypingSpeed::FAST);

		// ���� ���� - ������ ���� �Է� �ȳ� (�ִ� ����)
		strAsk_HowMany.clear();
		strAsk_HowMany += to_string(quantity_possibleMAX);
		PrintBySpellingWithColor(strAsk_HowMany, EColors::LIGHT_YELLOW, ETypingSpeed::FAST);

		strAsk_HowMany.clear();
		if (!mIsSpecialShop)
		{// �Ϲ� ����

			if (quantity_possibleMAX == ONE)
			{
				strAsk_HowMany += "������ ���� �����մϴ�.\n������ ������ �Է��ϼ���.\n";
			}
			else
			{
				strAsk_HowMany += "������ ���� �����մϴ�.\n������ ������ �Է��ϼ���. (1 ~ ";
			}
		}
		else
		{// Ư�� ����
			if (quantity_possibleMAX == ONE)
			{
				strAsk_HowMany += "���l ���ଫ ��r����LI����.\n���ଫ�� ������ �Է©̫ѤĿ�.\n";
			}
			else
			{
				strAsk_HowMany += "���l ���ଫ ��r����LI����.\n���ଫ�� ������ �Է©̫ѤĿ�. (1 ~ ";
			}
		}

		if (quantity_possibleMAX != ONE)
		{// ������ 1�� �̻��� ���
			strAsk_HowMany += to_string(quantity_possibleMAX);
			strAsk_HowMany += ")\n";
		}
		PrintBySpellingWithColor(strAsk_HowMany, EColors::YELLOW, ETypingSpeed::FAST);

		// �Է�
		const string chkedStr_HowMany = CheckInputValidation(1, quantity_possibleMAX, player); // ������ 1�� �̻�, ���� ������ �ִ�ġ ���Ϸ� �Է¹޴´�.
		digit_Quantity = stoi(chkedStr_HowMany);

		//==========================================
		// ���� ���� ����
		//==========================================
		// ���԰� ��� : 1�� ���� ���Ű��� �Ǹ��� ������ ������ ��������.
		price *= digit_Quantity;

		// ��� - ���� ���
		string strBuyResult = "";
		if (!mIsSpecialShop)
		{// �Ϲ� ����
			strBuyResult = "���� ��� : ";
		}
		else
		{// Ư�� ����
			if (EItemSpecial::HolyWater == static_cast<EItemSpecial>(key_digit))
			{
				vector<string> vecAsciiArt_HolySpirit;
				vecAsciiArt_HolySpirit = {

				};
				PrintByLineWithColor(vecAsciiArt_HolySpirit, EColors::LIGHT_YELLOW, ETypingSpeed::FAST);
				cout << endl;
			}
			strBuyResult = "���ଫ ��� : ";
		}

		PrintBySpellingWithColor(strBuyResult, EColors::LIGHT_YELLOW, ETypingSpeed::FAST);
		strBuyResult.clear();
		strBuyResult += "\"";

		if (!mIsSpecialShop)
		{// �Ϲ� ����
			strBuyResult += mCatalog_Reugular[static_cast<EItemRegular>(key_digit)]->getName();
		}
		else
		{// Ư�� ����
			strBuyResult += mCatalog_Special[static_cast<EItemSpecial>(key_digit)]->getName();
		}

		strBuyResult += "\" ";
		PrintBySpellingWithColor(strBuyResult, EColors::LIGHT_CYAN, ETypingSpeed::FAST);
		strBuyResult.clear();
		strBuyResult += to_string(digit_Quantity);

		if (!mIsSpecialShop)
		{// �Ϲ� ����
			strBuyResult += "�� ����, ";
		}
		else
		{// Ư�� ����
			strBuyResult = "�� ���ଫ, ";
		}

		PrintBySpellingWithColor(strBuyResult, EColors::YELLOW, ETypingSpeed::FAST);
		strBuyResult.clear();
		strBuyResult += "-";
		strBuyResult += to_string(price);
		strBuyResult += "(G)\n";
		PrintBySpellingWithColor(strBuyResult, EColors::LIGHT_CYAN, ETypingSpeed::FAST);

		// �÷��̾� ���� ��� ����
		player->setGold(player->getGold() - price);

		if (!mIsSpecialShop)
		{// �Ϲ� ����
			// �α� ������Ʈ
			UpdateLogMessage(true, mCatalog_Reugular[static_cast<EItemRegular>(key_digit)]->getName(), digit_Quantity);

			// �÷��̾�� ������ �ֱ�
			RegisterItem(player, static_cast<EItemRegular>(key_digit), digit_Quantity);

			// ��� - �÷��̾� �κ��丮
			DisplayPlayerInventory(player, false, true, static_cast<EItemRegular>(key_digit));
		}
		else
		{// Ư�� ����
			// �α� ������Ʈ
			UpdateLogMessage(true, mCatalog_Special[static_cast<EItemSpecial>(key_digit)]->getName(), digit_Quantity);

			// �÷��̾�� ������ �ֱ�
			RegisterItem(player, static_cast<EItemSpecial>(key_digit), digit_Quantity);

			// ��� - �÷��̾� �κ��丮
			DisplayPlayerInventory(player, false, true, static_cast<EItemSpecial>(key_digit));
		}

		//==========================================
		// �߰� ���� �Ұ� (��� < ������)
		//==========================================
		if (!IsEnoughGoldBuyLowestPrice(player))
		{// ���� �Ұ�
			PrintPurchaseNotPossible(player, true);

			//==========================================
			// ȸ�� - ���� �޴�
			//==========================================
			isContinue = false; continue;
		}

		//==========================================
		// �߰� ���� ���� (��� >= ������)
		//==========================================
		// ��� - �÷��̾� ���� �ݾ�
		PrintPlayerGold(player, true);

		// ���� - Yes/No
		string strAsk_More = "";
		if (!mIsSpecialShop)
		{// �Ϲ� ����
			strAsk_More = "�� �����Ͻðڽ��ϱ�?\n";
		}
		else
		{// Ư�� ����
			strAsk_More = "�Ʀ� ���ଫ�̪󩥰ڽ�LI��?\n";
		}
		PrintBySpellingWithColor(strAsk_More, EColors::YELLOW, ETypingSpeed::FAST);

		// �Է� - Yes/No
		if (!IsYes(player))
		{
			//==========================================
			// ȸ�� - ���� �޴�
			//==========================================
			isContinue = false; continue;
		}
	}//END-while (isContinue)
}//END-void Shop::BuyItem

void Shop::SellItem(Character* player)
{
	bool isContinue = true;
	while (isContinue)
	{
		//==========================================
		// ��� - �ŷ� �α�
		//==========================================
		system("cls"); // ȭ�� �����
		PrintLog();

		//==========================================
		// ��� - �ƽ�Ű��Ʈ(Sales)
		//==========================================
		PrintAsciiArt(static_cast<int>(EMenu::Sell));

		// ��� - ���� ������ ������
		if (!mIsSpecialShop)
		{// �Ϲ� ����
			FnSetTextColor(EColors::LIGHT_YELLOW);	cout << "[0] �������� ���ư���\n";
		}
		else
		{// Ư�� ����
			FnSetTextColor(EColors::LIGHT_YELLOW);	cout << "[0] ��l������ ����r��r��l\n";
		}

		//==========================================
		// �Ǹ� �Ұ� (�κ��丮�� ����ִ� ���)
		//==========================================
		if (player->getInventory().empty())
		{
			PrintSaleNotPossible(player, false);

			//==========================================
			// ȸ�� - ���� �޴�
			//==========================================
			isContinue = false; continue;
		}

		//==========================================
		// �Ǹ� ���� (�κ��丮�� ä���� ���)
		//==========================================
		// ��� - �κ��丮, ���� ��差
		if (!mIsSpecialShop)
		{// �Ϲ� ����
			DisplayPlayerInventory<EItemRegular>(player, true);
		}
		else
		{// Ư�� ����
			DisplayPlayerInventory<EItemSpecial>(player, true);
		}

		// ��� - �÷��̾� ���� �ݾ�
		PrintPlayerGold(player, true);

		// ���� - �Ǹ��� ������
		string strAsk_SelectItem = "";
		if (!mIsSpecialShop)
		{// �Ϲ� ����
			strAsk_SelectItem = "\"�κ��丮 ���\"����, �Ǹ��Ϸ��� ������ ��ȣ�� �ϳ��� �����ϼ���.\n���� �޴��� ���ư����� ���� 0���� �����ϼ���.\n";
		}
		else
		{// Ư�� ����
			strAsk_SelectItem = "\"�κ�����l ���\"����ln��, �ǡଫ�̷��� ��r��l�� ��ȣ�� �̤�rϢ�� ���é̫ѤĿ�.\n��l�� �޴��� ����r��r���� ������ 0���� ���é̫ѤĿ�.\n";
		}
		PrintBySpellingWithColor(strAsk_SelectItem, EColors::YELLOW, ETypingSpeed::FAST);

		//==========================================
		// ���� - Ű�� & �Է°� 
		//==========================================
		map<string, pair<Item*, int>> playerInventory = player->getInventory();
		vector<string> vecChkIdx;
		map<string, pair<Item*, int>>::iterator it;
		for (it = playerInventory.begin(); it != playerInventory.end(); ++it)
		{
			vecChkIdx.push_back(it->first);
		}

		//==========================================
		// �Է�(1) - ������ ��ȣ
		//==========================================
		const string chkedStr_SelectItem = CheckInputValidation(0, playerInventory.size(), player);
		const int digit_SelectItemIdx = stoi(chkedStr_SelectItem);

		// "�������� ���ư���" ���� ��
		const int Exit = 0;
		if (Exit == digit_SelectItemIdx)
		{
			//==========================================
			// ȸ�� - ���� �޴�
			//==========================================
			isContinue = false; continue;
		}

		//==========================================
		// ������ �������� ���� ����
		//==========================================
		// �Է°��� ���� �κ��丮 �ε����� �����ϱ� ���� Ű
		const string strKey = vecChkIdx[digit_SelectItemIdx - 1];			// key-name. ȭ��� ���ù�ȣ�� 1�������̹Ƿ� -1 ó����.
		const int quantity = playerInventory.find(strKey)->second.second;	// ����
		Item* item = playerInventory.find(strKey)->second.first;			// ������ Ÿ��
		const string strItemDefaultName = item->getName();					// ������ �⺻ �̸�
		int salePrice = (item->getPrice()) * mSaleRatio;					// ���԰�
		int digit_Quantity = 0;												// ���� �Ǹ��� ������ ����

		const int ONLY_ONE = 1;
		if (ONLY_ONE == quantity)
		{
			//==========================================
			// ������ �������� ������ 1������ ���
			//==========================================
			// ���� - �Ǹ��� ������
			string strAsk_SellReally = "";
			if (!mIsSpecialShop)
			{// �Ϲ� ����
				strAsk_SellReally = "������ �������� ���� 1������ �������Դϴ�. ������ �Ǹ��Ͻðڽ��ϱ�?\n";
			}
			else
			{// Ư�� ����
				strAsk_SellReally = "���ä��� ��r��l���� ���� 1������ ��r��l����LI����. ������ �ǡଫ�̪󩥰ڽ�LI��?\n";
			}
			PrintBySpellingWithColor(strAsk_SellReally, EColors::LIGHT_RED, ETypingSpeed::FAST);

			if (!IsYes(player))
			{
				//==========================================
				// ȸ�� - ���� �޴�
				//==========================================
				//isContinue = false;
				continue;
			}

			const int ONLY_ONE = 1;	// �Ǹ��� ������ ������ 1���� ����
			digit_Quantity = ONLY_ONE;
		}
		else
		{
			//==========================================
			// �Է�(2) - ����
			//==========================================
			// ���� ������ ���
			string strAsk_HowMany = "";
			if (!mIsSpecialShop)
			{// �Ϲ� ����
				strAsk_HowMany += "������ �������� ���� ";
			}
			else
			{// Ư�� ����
				strAsk_HowMany += "���ä��� ��r��l���� ���� ";
			}
			PrintBySpellingWithColor(strAsk_HowMany, EColors::YELLOW, ETypingSpeed::FAST);
			strAsk_HowMany.clear();
			strAsk_HowMany += to_string(quantity);
			PrintBySpellingWithColor(strAsk_HowMany, EColors::LIGHT_YELLOW, ETypingSpeed::FAST);
			strAsk_HowMany.clear();
			if (!mIsSpecialShop)
			{// �Ϲ� ����
				strAsk_HowMany += "�� �ֽ��ϴ�.\n�Ǹ��� ������ �Է��ϼ���. (1 ~ ";
			}
			else
			{// Ư�� ����
				strAsk_HowMany += "�� �ֽ�LI����.\n�ǡଫ�� ������ �Է©̫ѤĿ�. (1 ~ ";
			}
			strAsk_HowMany += to_string(quantity);
			strAsk_HowMany += ")\n";
			PrintBySpellingWithColor(strAsk_HowMany, EColors::YELLOW, ETypingSpeed::FAST);

			// �Է�
			const string chkedStr_HowMany = CheckInputValidation(1, quantity, player);	// ������ 1�� �̻�, ������ �������� ���� ���Ϸ� �Է¹޴´�.
			digit_Quantity = stoi(chkedStr_HowMany);
		}

		//==========================================
		// �Ǹ� ���� ����
		//==========================================
		// ���԰� ��� : 1�� ���� ���԰��� �Ǹ��� ������ ������ ��������.
		salePrice *= digit_Quantity;

		// ��� - �Ǹ� ���� ����
		string strBuyResult = "";
		if (!mIsSpecialShop)
		{// �Ϲ� ����
			strBuyResult = "�Ǹ� ���: ";
			PrintBySpellingWithColor(strBuyResult, EColors::LIGHT_YELLOW, ETypingSpeed::FAST);
			strBuyResult.clear();
			strBuyResult += "\"";
			strBuyResult += strKey;
			strBuyResult += "\"(Type: ";
			strBuyResult += strItemDefaultName;
			strBuyResult += ") ";
			PrintBySpellingWithColor(strBuyResult, EColors::LIGHT_CYAN, ETypingSpeed::FAST);
			strBuyResult.clear();
			strBuyResult += to_string(digit_Quantity);
			strBuyResult += "�� �Ǹ�, ";
			PrintBySpellingWithColor(strBuyResult, EColors::YELLOW, ETypingSpeed::FAST);
			strBuyResult.clear();
			strBuyResult += "+";
			strBuyResult += to_string(salePrice);
			strBuyResult += "(G)\n";
			PrintBySpellingWithColor(strBuyResult, EColors::LIGHT_CYAN, ETypingSpeed::FAST);
		}
		else
		{// Ư�� ����
			strBuyResult = "�ǡଫ ���: ";
			PrintBySpellingWithColor(strBuyResult, EColors::LIGHT_YELLOW, ETypingSpeed::FAST);
			strBuyResult.clear();
			strBuyResult += "\"";
			strBuyResult += strKey;
			strBuyResult += "\"(Type: ";
			strBuyResult += strItemDefaultName;
			strBuyResult += ") ";
			PrintBySpellingWithColor(strBuyResult, EColors::LIGHT_CYAN, ETypingSpeed::FAST);
			strBuyResult.clear();
			strBuyResult += to_string(digit_Quantity);
			strBuyResult += "�� �ǡଫ, ";
			PrintBySpellingWithColor(strBuyResult, EColors::YELLOW, ETypingSpeed::FAST);
			strBuyResult.clear();
			strBuyResult += "+";
			strBuyResult += to_string(salePrice);
			strBuyResult += "(G)\n";
			PrintBySpellingWithColor(strBuyResult, EColors::LIGHT_CYAN, ETypingSpeed::FAST);
		}

		// ���� �߿�! ���� ������ �Ǹ� ���� ���� ���� �α� ������Ʈ�� ���� �����ؾ� ��.
		// �α� ������Ʈ
		UpdateLogMessage(false, strItemDefaultName, digit_Quantity);

		// �÷��̾�� �ݾ� ����
		player->setGold(player->getGold() + salePrice);

		// �κ��丮 ���� ����
		ReduceItem(player, strKey, digit_Quantity);

		//==========================================
		// �߰� �Ǹ� �Ұ� (�κ��丮�� ����ִ� ���)
		//==========================================
		if (player->getInventory().empty())
		{// �Ǹ� �Ұ�
			PrintSaleNotPossible(player, true);

			//==========================================
			// ȸ�� - ���� �޴�
			//==========================================
			isContinue = false; continue;
		}

		//==========================================
		// �߰� �Ǹ� ����
		//==========================================
		// ��� - �κ��丮
		if (!mIsSpecialShop)
		{// �Ϲ� ����
			DisplayPlayerInventory(player, true, true, EItemRegular::END, strKey);
		}
		else
		{// Ư�� ����
			DisplayPlayerInventory(player, true, true, EItemSpecial::END, strKey);
		}

		// ��� - �÷��̾� ���� �ݾ�
		PrintPlayerGold(player, true);

		// ���� - Yes/No
		string strAsk_More = "";
		if (!mIsSpecialShop)
		{// �Ϲ� ����
			strAsk_More = "�� �Ǹ��Ͻðڽ��ϱ�?\n";
		}
		else
		{// Ư�� ����
			strAsk_More = "�Ʀ� �ǡଫ�̪󩥰ڽ�LI��?\n";
		}
		PrintBySpellingWithColor(strAsk_More, EColors::YELLOW, ETypingSpeed::FAST);

		if (!IsYes(player))
		{
			//==========================================
			// ȸ�� -  ���� �޴�
			//==========================================
			isContinue = false; continue;
		}
	}//END-while (isContinue)
}//END-void Shop::SellItem

void Shop::PrintAsciiArt(int _type)
{
	// �Ϲ� ������
	vector<string> vecAsciiArt;
	vecAsciiArt.clear();
	EColors color = EColors::END;

	// Ư�� ������
	// ���ʹ� �� �پ� ��µǹǷ�, ���ڿ��� ó���Ͽ� ö�� �ϳ��� ����ϴ� ������� ����.
	string strAsciiArt = "";

	EMenu type = static_cast<EMenu>(_type);
	switch (type)
	{
	case EMenu::Main:
	{// MainMenu
		if (!mIsSpecialShop)
		{// �Ϲ� ����
			vecAsciiArt = {
				"___  ___        _        ___  ___                     ",
				"|  \\/  |       (_)       |  \\/  |                     ",
				"| .  . |  __ _  _  _ __  | .  . |  ___  _ __   _   _  ",
				"| |\\/| | / _` || || '_ \\ | |\\/| | / _ \\| '_ \\ | | | | ",
				"| |  | || (_| || || | | || |  | ||  __/| | | || |_| | ",
				"\\_|  |_/ \\__,_||_||_| |_|\\_|  |_/ \\___||_| |_| \\__,_| "
			};
			color = EColors::LIGHT_MAGENTA;
		}
		else
		{// Ư�� ����
			strAsciiArt += "___  ___        _        ___  ___                     ";
			strAsciiArt += "\n|���\\/���|       (��)       |���\\/���|                     ";
			strAsciiArt += "\n|�������|  __ _  _  _ __  |�������|  ___  _ __   _   _  ";
			strAsciiArt += "\n|��|\\/|��| /�����||��||�����\\ |��|\\/|��| /����\|������\\ |��| |��| ";
			strAsciiArt += "\n|��|  |��||��(_|��||��||��| |��||��|  |��||�����/|��| |��||��|_|��| ";
			strAsciiArt += "\n\\��|  |��/ \\�����||��||��| |��|\\��|  |��/ \\����||��| |��| \\�����| ";
		}
	}
	break;
	case EMenu::Buy:
	{// Purchase

		if (!mIsSpecialShop)
		{// �Ϲ� ����
			vecAsciiArt = {
				"______                     _                        ",
				"| ___ \\                   | |                       ",
				"| |_/ / _   _  _ __   ___ | |__    __ _  ___   ___  ",
				"|  __/ | | | || '__| / __|| '_ \\  / _` |/ __| / _ \\ ",
				"| |    | |_| || |   | (__ | | | || (_| |\\__ \\|  __/ ",
				"\\_|     \\__,_||_|    \\___||_| |_| \\__,_||___/ \\___| "
			};
			color = EColors::LIGHT_GREEN;
		}
		else
		{// Ư�� ����
			strAsciiArt += "______                     _                        ";
			strAsciiArt += "\n|������\\                   |��|                       ";
			strAsciiArt += "\n|��|_/��/ _   _  _ __   ___ |��|__    __ _  ___   ___  ";
			strAsciiArt += "\n|�����/ |��| |��||�����| /����||�����\\  /��_���|/ ���| /����\\ ";
			strAsciiArt += "\n|��|    |��|_|��||��|   |��(__ |��| |��||��(_|��|\\��� \\|�����/ ";
			strAsciiArt += "\n\\��|     \\�����||��|   \\�����||��| |��| \\�����||����/ \\����| ";
		}
	}
	break;
	case EMenu::Sell:
	{// Sales
		if (!mIsSpecialShop)
		{// �Ϲ� ����
			vecAsciiArt = {
				" _____         _                ",
				"/  ___|       | |               ",
				"\\ `--.   __ _ | |  ___  ___    ",
				" `--. \\ / _` || | / _ \\/ __|  ",
				"/\\__/ /| (_| || ||  __/\\__ \\ ",
				"\\____/  \\__,_||_| \\___||___/ "
			};
			color = EColors::LIGHT_BLUE;
		}
		else
		{// Ư�� ����
			strAsciiArt += " _____         _                ";
			strAsciiArt += "\n/������|       |��|               ";
			strAsciiArt += "\n\\��`--.   __ _ |��|  ___  ___    ";
			strAsciiArt += "\n `--.��\\ /�����||��| /����\\/����|  ";
			strAsciiArt += "\n/\\__/��/|��(_|��||��||�����/\\����\\ ";
			strAsciiArt += "\n\\�����/  \\�����||��| \\����||����/ ";
		}
	}
	break;
	case EMenu::Exit:
	{//Caution

		color = EColors::RED;
		if (!mIsSpecialShop)
		{// �Ϲ� ����
			vecAsciiArt = {
			" _____                _    _                ",
			"/������\\              |��|  (��)               ",
			"|��/  \\/  __ _  _   _ |��|_  _   ___   _ __   ",
			"|��|     /�����||��| |��||����||��| /����\\ |�����\\  ",
			"|��\\__/\\|��(_|��||��|_|��||��|_ |��||��(_)��||��| |��| ",
			" \\�����/ \\�����| \\�����| \\���||��| \\����/ |��| |��| "
			};
		}
		else
		{// Ư�� ����
			strAsciiArt += " _____                _    _                ";
			strAsciiArt += "\n/������\\              |��|  (��)               ";
			strAsciiArt += "\n|��/  \\/  __ _  _   _ |��|_  _   ___   _ __   ";
			strAsciiArt += "\n|��|     /�����||��| |��||����||��| /����\\ |�����\\  ";
			strAsciiArt += "\n|��\\__/\\|��(_|��||��|_|��||��|_ |��||��(_)��||��| |��| ";
			strAsciiArt += "\n \\�����/ \\�����| \\�����| \\���||��| \\����/ |��| |��| ";
		}
	}
	break;
	case EMenu::END:
		break;
	default:
		break;
	}

	if (!mIsSpecialShop)
	{// �Ϲ� ����
		PrintByLineWithColor(vecAsciiArt, color, ETypingSpeed::SLOW);
	}
	else
	{// Ư�� ����
		vector<int> colors = {
			static_cast<int>(EColors::GREEN),
			static_cast<int>(EColors::RED),
			static_cast<int>(EColors::LIGHT_CYAN),
			static_cast<int>(EColors::LIGHT_BLUE),
			static_cast<int>(EColors::YELLOW)
		};
		for (size_t i = 0; i < strAsciiArt.size(); ++i)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colors[i % colors.size()]);
			if (strAsciiArt[i] == '\n')
			{
				FnSleep(100);
			}
			cout << strAsciiArt[i];
		}
		cout << endl;
	}

	cout << endl;
}//END-void Shop::PrintAsciiArt

void Shop::PrintPlayerGold(Character* player, bool _isEnoughGold)
{
	EColors color = EColors::END;
	string strPlayerGold1;
	// ��� - �÷��̾� ���� �ݾ�
	if (!mIsSpecialShop)
	{// �Ϲ� ����
		strPlayerGold1 = "���� ���� ���� ���: ";
	}
	else
	{// Ư�� ����
		strPlayerGold1 = "���� �ҫ�l ���� ���: ";
	}
	PrintBySpellingWithColor(strPlayerGold1, EColors::YELLOW, ETypingSpeed::FAST);

	// ��� ����
	if (_isEnoughGold)
	{// ����� ���
		color = EColors::LIGHT_YELLOW;
	}
	else
	{// ������� ���� ��� - ����� �������� RED
		color = EColors::RED;
	}
	string strPlayerGold2;
	strPlayerGold2.append(to_string(player->getGold()));
	strPlayerGold2.append("(G)\n");

	PrintBySpellingWithColor(strPlayerGold2, color, ETypingSpeed::FAST);
	cout << endl;
}//END-void Shop::PrintPlayerGold

void Shop::PrintYesNoMenu()
{
	FnSetTextColor(EColors::LIGHT_YELLOW);	cout << "[1] ";
	FnSetTextColor(EColors::YELLOW);		cout << "YES\n";
	FnSetTextColor(EColors::LIGHT_YELLOW);	cout << "[2] ";
	if (!mIsSpecialShop)
	{// �Ϲ� ����
		FnSetTextColor(EColors::YELLOW);	cout << "NO (�������� ���ư���)\n";
	}
	else
	{// Ư�� ����
		FnSetTextColor(EColors::YELLOW);	cout << "NO (��l������ ����r��r��l)\n";
	}
	FnSetTextDefault();
}//END-void Shop::PrintYesNoMenu

void Shop::PrintEmptyInventoryMessage()
{
	string str = "";
	if (!mIsSpecialShop)
	{// �Ϲ� ����
		str = "�κ��丮�� ����ֽ��ϴ�.\n�������� �����Ͽ� �κ��丮�� ä��������.\n";
	}
	else
	{// Ư�� ����
		str = "�κ�����l��r ���ө����ֽ�LI����.\n��r��l���� ���ଫ�̩��� �κ�����l�� ä�����ѤĿ�.\n";
	}
	PrintBySpellingWithColor(str, EColors::LIGHT_RED, ETypingSpeed::FAST);
}//END-void Shop::PrintEmptyInventoryMessage

void Shop::PrintPurchaseNotPossible(Character* player, bool _isAdditional)
{
	// ��� - �÷��̾� ���� �ݾ�
	PrintPlayerGold(player, false);

	string str;
	if (!mIsSpecialShop)
	{// �Ϲ� ����
		if (_isAdditional)
		{// �߰� ������ ���
			str = "�� �̻� ���Ÿ� ������ �� �����ϴ�. ��尡 ������� �ʽ��ϴ�.\n";
		}
		else
		{// �ʱ� ������ ���
			str = "������ �� �����ϴ�. ��尡 ������� �ʽ��ϴ�.\n";
		}
		PrintBySpellingWithColor(str, EColors::LIGHT_RED, ETypingSpeed::FAST);

		const string strAsk = "���� �޴��� ���ư����� ���� 0���� �����ϼ���.\n";
		PrintBySpellingWithColor(strAsk, EColors::YELLOW, ETypingSpeed::FAST);
	}
	else
	{// Ư�� ����
		if (_isAdditional)
		{// �߰� ������ ���
			str = "�Ʀ� ��l��6 ���ଫ�� ������ �� ����LI����. ��夡r ��Щ̫�l �ʽ�LI����.\n";
		}
		else
		{// �ʱ� ������ ���
			str = "���ଫ�� �� ����LI����. ��夡r ��Щ̫�l �ʽ�LI����.\n";
		}
		PrintBySpellingWithColor(str, EColors::LIGHT_RED, ETypingSpeed::FAST);

		const string strAsk = "��l�� �޴��� ����r��r���� ������ 0���� ���é̫ѤĿ�.\n";
		PrintBySpellingWithColor(strAsk, EColors::YELLOW, ETypingSpeed::FAST);
	}

	// �Է� & ��ȿ�� �˻� (������ ��ȯ�� ���� ����)
	const string chkedStr = CheckInputValidation(0, 0, player);
}//END-void Shop::PurchaseNotPossible

void Shop::PrintSaleNotPossible(Character* player, bool _isAdditional)
{
	string str;
	if (!mIsSpecialShop)
	{// �Ϲ� ����
		if (_isAdditional)
		{// �߰� �Ǹ��� ���
			str = "�� �̻� �ǸŸ� ������ �� �����ϴ�. �κ��丮�� ������ϴ�.\n";
		}
		else
		{// �ʱ� �Ǹ��� ���
			str = "�Ǹ��� �� �ִ� �������� �����ϴ�. �κ��丮�� ����ֽ��ϴ�.\n";
		}
		PrintBySpellingWithColor(str, EColors::LIGHT_RED, ETypingSpeed::FAST);

		const string strAsk = "���� �޴��� ���ư����� ���� 0���� �����ϼ���.\n";
		PrintBySpellingWithColor(strAsk, EColors::YELLOW, ETypingSpeed::FAST);
	}
	else
	{// Ư�� ����
		if (_isAdditional)
		{// �߰� �Ǹ��� ���
			str = "�Ʀ� ��l��6 �ǡଫ�� ������ �� ����LI����. �κ�����l��r ���Ӿ���LI����.\n";
		}
		else
		{// �ʱ� �Ǹ��� ���
			str = "�ǡଫ�� �� �ִ� ��r��l�ۡ�l ����LI����. �κ�����l��r ���ө����ֽ�LI����.\n";
		}
		PrintBySpellingWithColor(str, EColors::LIGHT_RED, ETypingSpeed::FAST);

		const string strAsk = "��l�� �޴��� ����r��r���� ������ 0���� ���é̫ѤĿ�.\n";
		PrintBySpellingWithColor(strAsk, EColors::YELLOW, ETypingSpeed::FAST);
	}

	// �Է� & ��ȿ�� �˻� (������ ��ȯ�� ���� ����)
	const string chkedStr = CheckInputValidation(0, 0, player);
}//END-void Shop::SaleNotPossible

bool Shop::IsEnoughGoldBuyLowestPrice(Character* player)
{
	bool returnValue = false;

	// ��ǰ �� �ּ� ���� ã��
	vector<int> vecPrice;

	if (!mIsSpecialShop)
	{// �Ϲ� ����
		for (const pair<const EItemRegular, unique_ptr<Item>>& pair : mCatalog_Reugular)
		{
			vecPrice.push_back(pair.second->getPrice());
		}
	}
	else
	{// Ư�� ����
		for (const pair<const EItemSpecial, unique_ptr<Item>>& pair : mCatalog_Special)
		{
			vecPrice.push_back(pair.second->getPrice());
		}
	}

	// ��ǰ �� �ּ� ����
	const int minPrice = *std::min_element(vecPrice.begin(), vecPrice.end());
	if (minPrice <= player->getGold())
	{// ��尡 ����� ��� ��ȯ���� true
		returnValue = true;
	}

	return returnValue;
}//END-bool Shop::IsEnoughGoldBuyLowestPrice

bool Shop::IsYes(Character* player)
{
	bool returnValue = false;

	PrintYesNoMenu();

	// �Է�
	const string chkedStr = CheckInputValidation(static_cast<int>(EYesNo::Yes), static_cast<int>(EYesNo::No), player);
	const EYesNo result2 = static_cast<EYesNo>(stoi(chkedStr));
	switch (result2)
	{
	case EYesNo::Yes:
		returnValue = true;
		break;
	case EYesNo::No:
		break;
	case EYesNo::END:
		break;
	default:
		break;
	}

	return returnValue;
}//END-bool Shop::IsYes

void Shop::MainMenu(Character* player)
{
	bool isContinue = true;
	while (isContinue)
	{
		//==========================================
		// ��� - �ŷ� �α�
		//==========================================
		if (!mIsFirstEntry)
		{
			system("cls"); // ȭ�� �����
			PrintLog();
		}

		//==========================================
		// ��� - �ƽ�Ű��Ʈ(MainMenu)
		//==========================================
		PrintAsciiArt(static_cast<int>(EMenu::Main));

		//==========================================
		// �Է�(���ð�) - ���� or �Ǹ�
		//==========================================

		if (!mIsSpecialShop)
		{// �Ϲ� ����
			const string strAsk = "���ϴ� �޴��� �����ϼ���.\n";
			PrintBySpellingWithColor(strAsk, EColors::YELLOW, ETypingSpeed::FAST);

			FnSetTextColor(EColors::LIGHT_YELLOW);	cout << "[1] ";
			FnSetTextColor(EColors::YELLOW);		cout << "������ ����\n";
			FnSetTextColor(EColors::LIGHT_YELLOW);	cout << "[2] ";
			FnSetTextColor(EColors::YELLOW);		cout << "������ �Ǹ�\n";
			FnSetTextColor(EColors::LIGHT_YELLOW);	cout << "[3] ";
			FnSetTextColor(EColors::YELLOW);		cout << "���� ������\n";
			FnSetTextDefault();
		}
		else
		{// Ư�� ����
			const string strAsk = "���̴� �޴��� ���é̫ѤĿ�.\n";
			PrintBySpellingWithColor(strAsk, EColors::YELLOW, ETypingSpeed::FAST);

			FnSetTextColor(EColors::LIGHT_YELLOW);	cout << "[1] ";
			FnSetTextColor(EColors::YELLOW);		cout << "��r��l�� ���ଫ\n";
			FnSetTextColor(EColors::LIGHT_YELLOW);	cout << "[2] ";
			FnSetTextColor(EColors::YELLOW);		cout << "��r��l�� �ǡଫ\n";
			FnSetTextColor(EColors::LIGHT_YELLOW);	cout << "[3] ";
			FnSetTextColor(EColors::YELLOW);		cout << "���� ��r��r��l\n";
			FnSetTextDefault();
		}

		// �Է�
		const string chkedStr = CheckInputValidation(static_cast<int>(EMenu::Buy), static_cast<int>(EMenu::Exit), player);
		const EMenu result = static_cast<EMenu>(stoi(chkedStr));

		mIsFirstEntry = false; // ù ���� ���� �ʱ�ȭ (false�� ����)

		//==========================================
		// �б� - ���� or �Ǹ�
		//==========================================
		// ����� ���� �帧�� ����
		switch (result)
		{
		case EMenu::Buy:
			BuyItem(player);
			break;
		case EMenu::Sell:
			SellItem(player);
			break;
		case EMenu::Exit:
			isContinue = !OnExit(player); // true ��ȯ �� ����
			break;
		default:
			break;
		}
	}
}//END-MainMenu

void Shop::ReduceItem(Character* player, string _strKey, int _quantity)
{
	/*
		Character Ŭ������ �κ��丮�Ƿ�
		�������� �κ��丮�� �������� �ʰ� ĳ���Ϳ��� ���� ������ ������ �Ѱ��ְ�
		�κ��丮 ������ ĳ���Ͱ� ���� ó���ϵ��� �Ѵ�.
		(ĳ���Ͱ� �κ��丮�� �����ϴ� å���� ������.)
	*/
	//map<string, pair<Item*, int>>& playerInventory = player->getInventory();
	//const int quantity = playerInventory.find(_strKey)->second.second; // ����

	//const int ONLY_ONE = 1;
	//if (ONLY_ONE == quantity)
	//{// ���� ������ 1���� ���
	//	delete playerInventory.find(_strKey)->second.first;	// ���� Item*�� �����ϰ�
	//	playerInventory.erase(_strKey);						// ������ ����
	//}
	//else
	//{// ���� ������ �ּ� 2�̻��� ���
	//	playerInventory.find(_strKey)->second.second--;		// ���� 1 ����
	//}

	player->removeItem(_strKey, _quantity);
}//END-void Shop::ReduceItem

string Shop::CheckInputValidation(int _min, int _max, Character* player, bool _isPurcahseMode)
{
	string returnValue = "";
	string strTmp = "";

	while (true)
	{
		cout << "�Է�: ";
		//cin.ignore();
		getline(std::cin, strTmp);

		if (strTmp.empty())
		{
			FnSetTextColor(EColors::LIGHT_RED);
			if (!mIsSpecialShop)
			{// �Ϲ� ����
				std::cout << "�Է°��� ����� �� �����ϴ�." << endl;
			}
			else
			{// Ư�� ����
				std::cout << "�Է°��� ���ӿ��� �� ����LI����." << endl;
			}
			FnSetTextDefault();
			continue;
		}
		if (strTmp.find(' ') != std::string::npos)
		{
			FnSetTextColor(EColors::LIGHT_RED);
			if (!mIsSpecialShop)
			{// �Ϲ� ����
				std::cout << "�Է°��� ������ ������ �� �����ϴ�." << endl;
			}
			else
			{// Ư�� ����
				std::cout << "�Է°��� ������ ����ͯ�� �� ����LI����." << endl;
			}
			FnSetTextDefault();
			continue;
		}

		bool isOk = false;
		try
		{
			const int digit = stoi(strTmp); // ���� �߻� ���ɼ� ����
			if ((!_isPurcahseMode) && (_min <= digit) && (digit <= _max))
			{// �Ϲ����� ���
				isOk = true;
				returnValue = strTmp;

				break;
			}
			else if (_isPurcahseMode)
			{// ���� ����� ���
				// �������� ���ư��⸦ ������ ���
				const int MIN = 0;
				if (MIN == digit)
				{
					isOk = true;
					returnValue = strTmp;
					break;
				}

				int MAX = -1;
				if (!mIsSpecialShop)
				{// �Ϲ� ����
					MAX = static_cast<int>(EItemRegular::END);
				}
				else
				{// Ư�� ����
					MAX = static_cast<int>(EItemSpecial::END);
				}

				if (digit <= MAX)
				{// ������ ����� ���� ��ȣ �̳��� �Է��� ���

					// ȭ��� ��ȣ�� ���� ��ȣ�� 1���� �����ϹǷ�, ���� ���ε� �ε����ʹ� 1���̰� ����.
					const int idx = digit - 1;

					int price = -1;
					// ������ �������� ����
					if (!mIsSpecialShop)
					{// �Ϲ� ����
						price = mCatalog_Reugular[static_cast<EItemRegular>(idx)]->getPrice();
					}
					else
					{// Ư�� ����
						price = mCatalog_Special[static_cast<EItemSpecial>(idx)]->getPrice();
					}

					// �÷��̾��� ���
					const int gold = player->getGold();

					if (price <= gold)
					{// ���� ������ ��� (������ �������� ���� <= �÷��̾��� ���) 
						isOk = true;
						returnValue = strTmp;
						break;
					}
					// ���� �������� ���� ���� if���� Ÿ�� ���Ѵ�. (������ �������� ���� > �÷��̾��� ���)
				}
			}
		}
		catch (const std::invalid_argument& e)
		{// stoi : ���ڰ� �ƴ� ���ڿ� �Է� ��
			FnSetTextColor(EColors::LIGHT_RED);
			if (!mIsSpecialShop)
			{// �Ϲ� ����
				cout << "���� ������ �ƴմϴ�." << endl;
			}
			else
			{// Ư�� ����
				cout << "������ ���ġ�l ��r��LI����." << endl;
			}
			FnSetTextDefault();
			continue;
		}
		catch (const std::out_of_range& e)
		{// stoi : �Է� ���ڰ� int ������ �ʰ��� ���
			FnSetTextColor(EColors::LIGHT_RED);
			if (!mIsSpecialShop)
			{// �Ϲ� ����
				cout << "�Է°��� �ʹ� Ů�ϴ�." << endl;
			}
			else
			{// Ư�� ����
				cout << "�Է°���l �ʹ� ŮLI����." << endl;
			}
			FnSetTextDefault();
			continue;
		}
		if (!isOk)
		{// �Է°��� ���ڿ��� ��ȿ�� ���� �ƴ� ���
			FnSetTextColor(EColors::LIGHT_RED);
			if (!mIsSpecialShop)
			{// �Ϲ� ����
				std::cout << "��ȿ�� �Է°��� �ƴմϴ�." << endl;
			}
			else
			{// Ư�� ����
				std::cout << "��ȿ���� �Է°���l ��r��LI����." << endl;
			}
			FnSetTextDefault();
			continue;
		}
	}
	cout << endl;
	return returnValue;
}//END-string Shop::CheckInputValidation

void Shop::CreateLog()
{
	if (!mIsSpecialShop)
	{// �Ϲ� ����
		for (const pair<const EItemRegular, unique_ptr<Item>>& pair : mCatalog_Reugular)
		{
			const unique_ptr<Item>& itemPtr = pair.second;
			const string name = itemPtr->getName(); // ������ �̸��� �����ͼ� ���

			mPurchaseLog[name] = 0;	// ���� �α� �ʱ�ȭ
			mSalesLog[name] = 0;	// �Ǹ� �α� �ʱ�ȭ
		}
	}
	else
	{// Ư�� ����
		for (const pair<const EItemSpecial, unique_ptr<Item>>& pair : mCatalog_Special)
		{
			const unique_ptr<Item>& itemPtr = pair.second;
			const string name = itemPtr->getName(); // ������ �̸��� �����ͼ� ���

			mPurchaseLog[name] = 0;	// ���� �α� �ʱ�ȭ
			mSalesLog[name] = 0;	// �Ǹ� �α� �ʱ�ȭ
		}
	}
}//END-void Shop::CreateLog

void Shop::PrintLog()
{
	// ��� - �α� ��� ��ó��
	FnSetTextColor(EColors::DARK_GRAY);
	string strLog = "History\n";
	strLog += "======================================================================================";
	cout << strLog << endl;
	strLog.clear();

	// ���� �α� ���
	FnSetTextColor(EColors::LIGHT_GREEN);
	if (!mIsSpecialShop)
	{// �Ϲ� ����
		strLog += "[����] ";
	}
	else
	{// Ư�� ����
		strLog += "[���ଫ] ";
	}
	for (const auto& entry : mPurchaseLog)
	{
		strLog += entry.first + ":" + to_string(entry.second) + "/ ";
	}
	strLog.erase(strLog.size() - 2); // ������ 3���� ����: "/  "
	cout << strLog << endl;
	strLog.clear();

	// �Ǹ� �α� ���
	FnSetTextColor(EColors::LIGHT_BLUE);
	if (!mIsSpecialShop)
	{// �Ϲ� ����
		strLog += "[�Ǹ�] ";
	}
	else
	{// Ư�� ����
		strLog += "[�ǡଫ] ";
	}
	for (const auto& entry : mSalesLog)
	{
		strLog += entry.first + ":" + to_string(entry.second) + "/ ";
	}
	strLog.erase(strLog.size() - 2); // ������ 3���� ����: " /  "
	cout << strLog << endl;
	strLog.clear();

	// ��� - �α� ��� ��ó��
	FnSetTextColor(EColors::DARK_GRAY);
	strLog += "======================================================================================";
	cout << strLog << endl;
	strLog.clear();

	// �⺻ �������� �ǵ�����
	FnSetTextDefault();
}//END-void Shop::PrintLog

void Shop::UpdateLogMessage(bool _isPurchase, string _key, int _quantity)
{
	if (_isPurchase)
	{// ���� �α� ������Ʈ
		mPurchaseLog[_key] += _quantity;
	}
	else
	{// �Ǹ� �α� ������Ʈ
		mSalesLog[_key] += _quantity;
	}
}//END-void Shop::UpdateLogMessage
