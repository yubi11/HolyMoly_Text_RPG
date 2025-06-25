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
	// 판매 중인 아이템 목록 세팅
	//==========================================
	if (!mIsSpecialShop)
	{// 일반 상점
		int size = static_cast<int>(EItemRegular::END);
		for (int i = 0; i < size; i++)
		{
			EItemRegular key = static_cast<EItemRegular>(i);
			switch (key)
			{
			case EItemRegular::HealthPotion:
				mCatalog_Regular[key] = std::make_unique<HealthPotion>();
				break;
			case EItemRegular::AttackBoost:
				mCatalog_Regular[key] = std::make_unique<AttackBoost>();
				break;
			case EItemRegular::ExpBook:
				mCatalog_Regular[key] = std::make_unique<ExpBook>();
				break;
			case EItemRegular::GoldBar:
				mCatalog_Regular[key] = std::make_unique<GoldBar>();
				break;
			case EItemRegular::rottenMeat:
				mCatalog_Regular[key] = std::make_unique<rottenMeat>();
				break;
			case EItemRegular::END:
				break;
			default:
				break;
			}
		}
	}
	else
	{// 특수 상점
		int size = static_cast<int>(EItemSpecial::END);
		for (int i = 0; i < size; i++)
		{
			EItemSpecial key = static_cast<EItemSpecial>(i);
			switch (key)
			{
			case EItemSpecial::HolyWater:
				mCatalog_Special[key] = std::make_unique<HolyWater>();
				break;
			case EItemSpecial::ChaosOrb:
				mCatalog_Special[key] = std::make_unique<ChaosOrb>();
				break;
			case EItemSpecial::END:
				break;
			default:
				break;
			}
		}
	}

	// 로그 메시지 초기화
	CreateLog();

	// 상점 시작
	OnEnter(player);
}

void Shop::OnEnter(Character* player)
{
	//==========================================
	// 출력 - 아스키아트 Only 최초진입
	//==========================================
	// 아스키아트
	vector<string> vecAsciiArt_Welcome;

	if (!mIsSpecialShop)
	{
		// 출력 - 아스키아트
		vecAsciiArt_Welcome = {
				"  _    _        _                                           ",
				" | |  | |      | |                                          ",
				" | |  | |  ___ | |  ___   ___   _ __ ___    ___             ",
				" | |/\\| | / _ \\| | / __| / _ \\ | '_ ` _ \\  / _ \\       ",
				" \\  /\\  /|  __/| || (__ | (_) || | | | | ||  __/          ",
				"  \\/  \\/  \\___||_| \\___| \\___/ |_| |_| |_| \\___|      ",
				"                                                            ",
				"  _gggggggggggmmgggggggggggggggggggmqggggggggggggggggggggp,				",
				"  @@@@@@@@@P      \"@ | [@@ | @@P       4@]      '@@@@@@@@@|				",
				"  @@@@@@@@@    \"\"4@@|  '\"\"   @g   @@@   @]  !B'  [@@@@@@@@|				",
				"  @@@@@@@@@Bm-__   @|  ,__,  @g   @@@   @]   ____@@@@@@@@@|				",
				"  @@@@@@@@@_      ,@|  [@@|  @@L       o@]  |@@@@@@@@@@@@@|				",
				"  0@@@@@@@@@@B@BB@@@BBBB@@@@@@@@@@@@B@@@@B@@BB@@@@@@@@@@@@'				",
				"  \\@@@@@@@@@/ @@@@@@@@@D Q@@@@@@@@@ \"@@@@@@@@@F @@@@@@@@@@ 				",
				"    *@@@@@F ,_ \"B@@@@P' _ '4@@@@B\" _, <@@@@@P ,_ \"B@@@@P'  				",
				"       ___+@@@@g______@@@@@______g@@@@a______@@@@g___      				",
				"       @@@@@@P==========@@@@@@BBBBBBBBBBBBBBBBBBB@@@@      				",
				"       @@@@@@           [@@@@@|                  @@@@             		",
				"       @@@@@@           [@@@@@|                  @@@@      				",
				"       @@@@@@           [@@@@@1__________________@@@@      				",
				"       @@@@@@           [@@@@@@@@@@@@@@@@@@@@@@@@@@@@      				",
				"       @@@@@@___________[@@@@@@@@@@@@@@@@@@@@@@@@@@@@      				",
				"       @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@      				",
				"  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@,				",
				"   \"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"      "
		};
		PrintByLineWithColor(vecAsciiArt_Welcome, EColors::LIGHT_CYAN, ETypingSpeed::FAST);
		cout << endl;

		// 출력 - 환영인사
		const string str_Welcome = "상점에 오신 것을 환영합니다!\n아이템을 구매하거나 판매해 보세요!\n\n\n";
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
		// 컬러 섞기
		vector<int> colors = {
			static_cast<int>(EColors::GREEN),
			static_cast<int>(EColors::RED),
			static_cast<int>(EColors::LIGHT_CYAN),
			static_cast<int>(EColors::LIGHT_BLUE),
			static_cast<int>(EColors::YELLOW)
		};
		// 출력 - 아스키아트
		for (size_t i = 0; i < vecAsciiArt_Welcome.size(); ++i)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colors[i % colors.size()]);
			cout << vecAsciiArt_Welcome[i] << endl;;
		}
		cout << endl;

		// 출력 - 환영인사
		const string str_Welcome = "상점øłl 오신 것을 환영합LI⊂ト!\nㅇr○l템을 구□Й㈛つㅓㄴr 판□ЙぁĦ 보パㅔ요!\n\n\n";
		PrintBySpellingWithColor(str_Welcome, EColors::YELLOW, ETypingSpeed::FAST);
	}

	//==========================================
	// 메인 메뉴
	//==========================================
	MainMenu(player);
}//END-void Shop::OnEnter

bool Shop::OnExit(Character* player)
{
	bool returnValue = false;
	//==========================================
	// 출력 - 거래 로그
	//==========================================
	system("cls"); // 화면 지우기
	PrintLog();

	//==========================================
	// 출력 - 아스키아트(Caution)
	//==========================================
	PrintAsciiArt(static_cast<int>(EMenu::Exit));

	// 출력 - 상점 나가기 선택지
	string str = "";
	if (!mIsSpecialShop)
	{// 일반 상점
		str = "이곳을 벗어나면 바로 전투가 시작됩니다.\n정말 나가시겠습니까?\n";
	}
	else
	{// 특수 상점
		str = "○l곳을 벗øłㄴr면 ㅂΓ로 전투ㄱr んı작됩LI⊂ト\n정말 ㄴrㄱrんı겠습LI까?\n";
	}
	PrintBySpellingWithColor(str, EColors::RED, ETypingSpeed::FAST);

	// 선택 - 상점 나가기
	if (IsYes(player))
	{
		returnValue = true;
	}

	FnSetTextDefault();
	return returnValue;
}//END-void Shop::OnExit

void Shop::DisplayItems(Character* player)
{
	// 특수 상점 - 아스키아트 라인 출력용
	vector<int> colors = {
		static_cast<int>(EColors::GREEN),
		static_cast<int>(EColors::RED),
		static_cast<int>(EColors::LIGHT_CYAN),
		static_cast<int>(EColors::LIGHT_BLUE),
		static_cast<int>(EColors::YELLOW)
	};
	string strLine = "◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆\n";

	//==========================================
	// 출력 - 아이템 목록 출력 전처리
	//==========================================
	const string str_Catalog = "판매 중인 아이템 목록:\n";
	const string str_Catalog2 = "판□Й 중인 ㅇr○l템 목록:\n";
	if (!mIsSpecialShop)
	{// 일반 상점
		// 출력 - 라인
		FnSetTextColor(EColors::LIGHT_GREEN);
		cout << "======================================================================================\n";
		// 출력 - 문구
		PrintBySpellingWithColor(str_Catalog, EColors::LIGHT_GREEN, ETypingSpeed::FAST);
	}
	else
	{// 특수 상점
		// 출력 - 라인
		for (size_t i = 0; i < strLine.size(); ++i)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colors[(i + 3) % colors.size()]);
			cout << strLine[i];
		}
		// 출력 - 문구
		PrintBySpellingWithColor(str_Catalog2, EColors::LIGHT_GREEN, ETypingSpeed::FAST);
	}

	//==========================================
	// 출력 - 아이템 목록
	//==========================================
	string str_effect;
	string strPrint;
	int idx = 1;
	if (!mIsSpecialShop)
	{// 일반 상점
		for (const pair<const EItemRegular, unique_ptr<Item>>& pair : mCatalog_Regular)
		{
			const EItemRegular& key = pair.first;			// 아이템 키 (EItemRegular 타입)
			const unique_ptr<Item>& itemPtr = pair.second;	// 아이템 포인터

			const int price = itemPtr->getPrice();			// 아이템 가격
			const int playerGold = player->getGold();		// 플레이어 소지 골드

			if (price > playerGold)
			{// 비활성화 : 현재 소지 중인 골드로는 구매할 수 없는 경우
				FnSetTextColor(EColors::DARK_GRAY);
				cout << "[" << idx++ << "] ";
			}
			else
			{// 활성화 : 골드가 충분해서 구매할 수 있는 경우
				// 인덱스만 강조, 사용자가 번호 입력을 할 때, 강조된 인덱스로 시각적 영향을 주어 선택이 편리하도록 함
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

			// 출력 - 아이템 이름 + 효과 + 가격
			strPrint = itemPtr->getName() + " (" + str_effect + " +" + to_string(itemPtr->getItemValue()) + ")";
			cout << left << setw(38) << strPrint			// 이름 + 효과 (38칸)
				<< ": " << right << setw(3) << price		// 가격 (3칸)
				<< "(G)" << endl;
		}
	}
	else
	{// 특수 상점
		for (const pair<const EItemSpecial, unique_ptr<Item>>& pair : mCatalog_Special)
		{
			const EItemSpecial& key = pair.first;			// 아이템 키 (EItemSpecial 타입)
			const unique_ptr<Item>& itemPtr = pair.second;  // 아이템 포인터

			const int price = itemPtr->getPrice();			// 아이템 가격
			const int playerGold = player->getGold();		// 플레이어 소지 골드

			if (price > playerGold)
			{// 비활성화 : 현재 소지 중인 골드로는 구매할 수 없는 경우
				FnSetTextColor(EColors::DARK_GRAY);
				cout << "[" << idx++ << "] ";
			}
			else
			{// 활성화 : 골드가 충분해서 구매할 수 있는 경우
				// 인덱스만 강조, 사용자가 번호 입력을 할 때, 강조된 인덱스로 시각적 영향을 주어 선택이 편리하도록 함
				FnSetTextColor(EColors::LIGHT_YELLOW);
				cout << "[" << idx++ << "] ";

				FnSetTextColor(EColors::YELLOW);
			}

			switch (key)
			{
			case EItemSpecial::HolyWater:	str_effect = "HP"; break;
			case EItemSpecial::ChaosOrb:	str_effect = "\"?\""; break;
			case EItemSpecial::END: break;
			default: break;
			}

			// 출력 - 아이템 이름 + 효과 + 가격
			if (EItemSpecial::HolyWater == key)
			{
				strPrint = itemPtr->getName() + " (" + str_effect + " +" + to_string(itemPtr->getItemValue()) + ")";
			}
			else if (EItemSpecial::ChaosOrb == key)
			{
				strPrint = itemPtr->getName() + "  (" + str_effect + ")";
			}

			cout << left << setw(38) << strPrint			// 이름 + 효과 (38칸)
				<< ": " << right << setw(3) << price		// 가격 (3칸)
				<< "(G)" << endl;
		}
	}
	//==========================================
	// 출력 - 아이템 목록 출력 후처리
	//==========================================
	if (!mIsSpecialShop)
	{// 일반 상점
		// 출력 - 라인
		FnSetTextColor(EColors::LIGHT_GREEN);
		cout << "======================================================================================\n";
	}
	else
	{// 특수 상점
		// 출력 - 라인
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
		// 출력 - 거래 로그
		//==========================================
		system("cls"); // 화면 지우기
		PrintLog();

		//==========================================
		// 출력 - 아스키아트(Purcahse)
		//==========================================
		PrintAsciiArt(static_cast<int>(EMenu::Buy));

		// 출력 - 상점 나가기 선택지	
		if (!mIsSpecialShop)
		{// 일반 상점
			FnSetTextColor(EColors::LIGHT_YELLOW);	cout << "[0] 이전으로 돌아가기\n";
		}
		else
		{// 특수 상점
			FnSetTextColor(EColors::LIGHT_YELLOW);	cout << "[0] ○l전으로 돌ㅇrㄱrブl\n";
		}

		// 출력 - 아이템 목록
		DisplayItems(player);

		//==========================================
		// 구매 가능성 확인
		//==========================================
		/*
			플레이어 소지 금액이
			상품 가격 중 최소 가격보다 적으면
			아이템을 선택할 수 없고
			이전 메뉴로 돌아가는 선택지만 제시한다.
		*/
		//==========================================
		// 구매 불가 (골드 < 최저가)
		//==========================================
		if (!IsEnoughGoldBuyLowestPrice(player))
		{
			PrintPurchaseNotPossible(player, false);

			//==========================================
			// 회귀 - 메인 메뉴
			//==========================================
			isContinue = false; continue;
		}

		//==========================================
		// 구매 가능 (골드 >= 최저가)
		//==========================================
		// 출력 - 플레이어 인벤토리 유무에 따라 분기
		if (!player->getInventory().empty())
		{// 인벤토리가 비어 있지 않은 경우
			if (!mIsSpecialShop)
			{// 일반 상점
				DisplayPlayerInventory<EItemRegular>(player, false);
			}
			else
			{// 특수 상점
				DisplayPlayerInventory<EItemSpecial>(player, false);
			}
		}
		else
		{// 인벤토리가 비어 있는 경우
			PrintEmptyInventoryMessage();
		}

		// 출력 - 플레이어 소지 금액
		PrintPlayerGold(player, true);

		// 선택 - 구매할 아이템
		string strAsk_SelectItem = "";
		if (!mIsSpecialShop)
		{// 일반 상점
			strAsk_SelectItem += "\"판매 중인 아이템 목록\"에서, 구매하려는 아이템 번호를 하나만 선택하세요.\n";
			strAsk_SelectItem += "이전 메뉴로 돌아가려면 숫자 0번을 선택하세요.\n";
		}
		else
		{// 특수 상점
			strAsk_SelectItem += "\"판□Й 중인 ㅇr○l템 목록\"øłlnㅓ, 구□Й㈛려는 ㅇr○l템 번호를 ㈛ㄴr口ざ 선택㈛パㅔ요.\n";
			strAsk_SelectItem += "○l전 메뉴로 돌ㅇrㄱr려면 숫ㅈΓ 0번을 선택㈛パㅔ요.\n";
		}
		PrintBySpellingWithColor(strAsk_SelectItem, EColors::YELLOW, ETypingSpeed::FAST);

		//==========================================
		// 입력(1) - 아이템 번호
		//==========================================
		int selection = -1;
		if (!mIsSpecialShop)
		{// 일반 상점
			selection = stoi(CheckInputValidation(0, mCatalog_Special.size(), player, true));
		}
		else
		{// 특수 상점
			selection = stoi(CheckInputValidation(0, mCatalog_Special.size(), player, true));
		}

		// 이전으로 돌아가기를 선택한 경우
		const int EXIT = 0;
		if (EXIT == selection)
		{
			//==========================================
			// 회귀 - 메인 메뉴
			//==========================================
			isContinue = false; continue;
		}

		//==========================================
		// 구매 가능성 확인 (골드 < 선택 아이템 가격)
		//==========================================
		const int key_digit = selection - 1; // 화면상 선택번호는 1번부터이므로 -1 처리함.
		int price = 0;

		if (!mIsSpecialShop)
		{// 일반 상점
			price = mCatalog_Regular[static_cast<EItemRegular>(key_digit)]->getPrice();
		}
		else
		{// 특수 상점
			price = mCatalog_Special[static_cast<EItemSpecial>(key_digit)]->getPrice();
		}

		if (price > player->getGold())
		{// 구매 불가
			PrintPurchaseNotPossible(player, false);

			//==========================================
			// 회귀 - 메인 메뉴
			//==========================================
			isContinue = false; continue;
		}

		//==========================================
		// 구매 가능 (골드 >= 선택 아이템 가격)
		//==========================================
		// 구매 가능한 최대 수량 찾기 (현재 골드량 / 아이템 가격 = 구매 가능한 최대 수량)
		int quantity_possibleMAX = player->getGold() / price;

		//==========================================
		// 입력(2) - 수량
		//==========================================
		int digit_Quantity = 0; // 구매할 아이템 수량
		const int ONE = 1;

		// 문장 조립 - 구매할 수량 입력 안내
		string strAsk_HowMany = "";
		if (!mIsSpecialShop)
		{// 일반 상점
			strAsk_HowMany += "선택한 아이템은 소지 중인 골드로 최대 ";
		}
		else
		{// 특수 상점
			strAsk_HowMany += "선택ㅎŁ ㅇr○l템은 소ズl 중인 골드로 최ㄷН ";
		}
		PrintBySpellingWithColor(strAsk_HowMany, EColors::YELLOW, ETypingSpeed::FAST);

		// 문장 조립 - 구매할 수량 입력 안내 (최대 수량)
		strAsk_HowMany.clear();
		strAsk_HowMany += to_string(quantity_possibleMAX);
		PrintBySpellingWithColor(strAsk_HowMany, EColors::LIGHT_YELLOW, ETypingSpeed::FAST);

		strAsk_HowMany.clear();
		if (!mIsSpecialShop)
		{// 일반 상점

			if (quantity_possibleMAX == ONE)
			{
				strAsk_HowMany += "개까지 구매 가능합니다.\n구매할 수량을 입력하세요.\n";
			}
			else
			{
				strAsk_HowMany += "개까지 구매 가능합니다.\n구매할 수량을 입력하세요. (1 ~ ";
			}
		}
		else
		{// 특수 상점
			if (quantity_possibleMAX == ONE)
			{
				strAsk_HowMany += "개까ズl 구□Й ㄱr능합LI⊂ト.\n구□Й할 수량을 입력㈛パㅔ요.\n";
			}
			else
			{
				strAsk_HowMany += "개까ズl 구□Й ㄱr능합LI⊂ト.\n구□Й할 수량을 입력㈛パㅔ요. (1 ~ ";
			}
		}

		if (quantity_possibleMAX != ONE)
		{// 수량이 1개 이상인 경우
			strAsk_HowMany += to_string(quantity_possibleMAX);
			strAsk_HowMany += ")\n";
		}
		PrintBySpellingWithColor(strAsk_HowMany, EColors::YELLOW, ETypingSpeed::FAST);

		// 입력
		const string chkedStr_HowMany = CheckInputValidation(1, quantity_possibleMAX, player); // 수량은 1개 이상, 골드로 가능한 최대치 이하로 입력받는다.
		digit_Quantity = stoi(chkedStr_HowMany);

		//==========================================
		// 구매 로직 진행
		//==========================================
		// 매입가 계산 : 1개 단위 구매가에 판매할 아이템 수량이 곱해진다.
		price *= digit_Quantity;

		// 출력 - 구매 결과
		string strBuyResult = "";
		if (!mIsSpecialShop)
		{// 일반 상점
			strBuyResult = "구매 결과 : ";
		}
		else
		{// 특수 상점
			if (EItemSpecial::HolyWater == static_cast<EItemSpecial>(key_digit))
			{
				vector<string> vecAsciiArt_HolySpirit;
				vecAsciiArt_HolySpirit = {

					"                             .                              ",
					"                            .@!                             ",
					"                        @,  |@|   r                         ",
					"                  _     '@  |@|  E'     ,                   ",
					"          'Sg_.    \"g_[1 | @' !P   _j\"    ._aB'           ",
					"              <Ta_   'Q_  '        _x\"   __Z >             ",
					"                 '4k__   .y@P=4Bg_   __gf                   ",
					"                     `  5`   _   \@  \"                     ",
					"             :@@@@@@b  !g .@\" \"B. [j  w@@@@@@-            ",
					"                       'B |@   @' (\"                       ",
					"              __agd4@g. TgJP   <1g\".g@B@gg__               ",
					"           _OP'      `@  J/     \\b  g        \"q_          ",
					"          @\"          faj        \\@ + W          '@       ",
					"         [/             @         @             'l          ",
					"       _g\"              @         @              '@,       ",
					"     _W\"                8,       ,@                \"@_    ",
					"    gL__       __@>Vm_   @.     .@   _jPT@__       ___Q  ",
					"       \"\"==BB=\"\"     \"9g__@     Ql_ > 0\"     \" += 8B = \"\"\"     ",
					"                          ]f   4[                           ",
					"                        ,@\"     \"B                        ",
					"                     _gP           Vg_                      ",
					"                     %g_           _JP                      ",
					"                       \"0qg__ - __agF\"                    "

				};
				PrintByLineWithColor(vecAsciiArt_HolySpirit, EColors::LIGHT_YELLOW, ETypingSpeed::FAST);
				cout << endl;
			}
			else if (EItemSpecial::ChaosOrb == static_cast<EItemSpecial>(key_digit))
			{
				vector<string> vecAsciiArt_HolySpirit;
				vecAsciiArt_HolySpirit = {
					"                              ___gWgg___                             ",
					"                      .__ggg@@@@@@@@@@@@@@@c___                      ",
					"               ___yW@@@@M\"   ___,,   '@@@@@@@@@@@@gp_,               ",
					"       .._~g@@@@@@@@@@@W.   3@@@@g   'BB@@@@@@@@@@@@@@@@@@g_,.       ",
					"            \"=9P@@@@@@@@g@@@@@@@@@@g_c    ,8@@@@@@@@@@[F>            ",
					"       |@@g__     \"=D@@@@@@@@@@@@@@@@@@@@@@@@@@@@P~     ,_g@@g       ",
					"       |@@@@@@WWg___    \"+NB@@@@@@@@@@@@@@BP\"     __<@@@@@@@@g       ",
					"       |@@@@@@@@@@@@@@y___    \"\"f@@@B@p\"     __@@@@@@@@@@@@@@g       ",
					"       |@@@@@@@@BPB]@@@@@@@Wg__       __g@@@@@@@@ABB@@@@@@@@@g       ",
					"       |@@@@@@        %@@@@@@@@@@   [@@@@@@@@@\"       ^$@@@@@g       ",
					"       |@@@@@B   _@g.   Z@@@@@@@@   [@@@@@@WP   ,g@_   [@@@@@g       ",
					"       |@@@@@@@@sg@@@   [@@@@@@@@   [@@@@@@@   j@@@@   [@@@@@g       ",
					"       |@@@@@@@@@@@W\"   [@@@@@@@@   [@@@@@@@@@@@@@F   _@@@@@@g       ",
					"       |@@@@@@@@@G^    _@@@@@@@@@   [@@@@@@@@@@@2    @@@@@@@@g       ",
					"       |@@@@@@@@@W   ;@@@@@@@@@@@   [@@@@@@@@@@@   ;@@@@@@@@@g       ",
					"       |@@@@@@@@@g___W@@@@@@@@@@@   [@@@@@@@@@@@ __9$@@@@@@@@g       ",
					"       |@@@@@@@@@@   @@@@@@@@@@@@   [@@@@@@@@@@@   |@@@@@@@@@g       ",
					"       'B@@@@@@@@@   @@@@@@@@@@@@   [@@@@@@@@@@@   |@@@@@@@@@g       ",
					"          ` v@@@@@@@@@@@@@@@@@@@@   [@@@@@@@@@@@@@@@@@@@B=\"          ",
					"                '\"4@@@@@@@@@@@@@@   [@@@@@@@@@@@@8B=                 ",
					"                      '\"4@@@@@@@@   [@@@@@@@Z*\"                      ",
					"                             \"0@@   [@@>\"                            "

				};
				PrintByLineWithColor(vecAsciiArt_HolySpirit, EColors::LIGHT_YELLOW, ETypingSpeed::FAST);
				cout << endl;
			}
			strBuyResult = "구□Й 결과 : ";
		}

		PrintBySpellingWithColor(strBuyResult, EColors::LIGHT_YELLOW, ETypingSpeed::FAST);
		strBuyResult.clear();
		strBuyResult += "\"";

		if (!mIsSpecialShop)
		{// 일반 상점
			strBuyResult += mCatalog_Regular[static_cast<EItemRegular>(key_digit)]->getName();
		}
		else
		{// 특수 상점
			strBuyResult += mCatalog_Special[static_cast<EItemSpecial>(key_digit)]->getName();
		}

		strBuyResult += "\" ";
		PrintBySpellingWithColor(strBuyResult, EColors::LIGHT_CYAN, ETypingSpeed::FAST);
		strBuyResult.clear();
		strBuyResult += to_string(digit_Quantity);

		if (!mIsSpecialShop)
		{// 일반 상점
			strBuyResult += "개 구매, ";
		}
		else
		{// 특수 상점
			strBuyResult = "개 구□Й, ";
		}

		PrintBySpellingWithColor(strBuyResult, EColors::YELLOW, ETypingSpeed::FAST);
		strBuyResult.clear();
		strBuyResult += "-";
		strBuyResult += to_string(price);
		strBuyResult += "(G)\n";
		PrintBySpellingWithColor(strBuyResult, EColors::LIGHT_CYAN, ETypingSpeed::FAST);

		// 플레이어 소지 골드 차감
		player->setGold(player->getGold() - price);

		if (!mIsSpecialShop)
		{// 일반 상점
			// 로그 업데이트
			UpdateLogMessage(true, mCatalog_Regular[static_cast<EItemRegular>(key_digit)]->getName(), digit_Quantity);

			// 플레이어에게 아이템 주기
			RegisterItem(player, static_cast<EItemRegular>(key_digit), digit_Quantity);

			// 출력 - 플레이어 인벤토리
			DisplayPlayerInventory(player, false, true, static_cast<EItemRegular>(key_digit));
		}
		else
		{// 특수 상점
			// 로그 업데이트
			UpdateLogMessage(true, mCatalog_Special[static_cast<EItemSpecial>(key_digit)]->getName(), digit_Quantity);

			// 플레이어에게 아이템 주기
			RegisterItem(player, static_cast<EItemSpecial>(key_digit), digit_Quantity);

			// 출력 - 플레이어 인벤토리
			DisplayPlayerInventory(player, false, true, static_cast<EItemSpecial>(key_digit));
		}

		//==========================================
		// 추가 구매 불가 (골드 < 최저가)
		//==========================================
		if (!IsEnoughGoldBuyLowestPrice(player))
		{// 구매 불가
			PrintPurchaseNotPossible(player, true);

			//==========================================
			// 회귀 - 메인 메뉴
			//==========================================
			isContinue = false; continue;
		}

		//==========================================
		// 추가 구매 가능 (골드 >= 최저가)
		//==========================================
		// 출력 - 플레이어 소지 금액
		PrintPlayerGold(player, true);

		// 선택 - Yes/No
		string strAsk_More = "";
		if (!mIsSpecialShop)
		{// 일반 상점
			strAsk_More = "더 구매하시겠습니까?\n";
		}
		else
		{// 특수 상점
			strAsk_More = "て┤ 구□Й㈛んı겠습LI까?\n";
		}
		PrintBySpellingWithColor(strAsk_More, EColors::YELLOW, ETypingSpeed::FAST);

		// 입력 - Yes/No
		if (!IsYes(player))
		{
			//==========================================
			// 회귀 - 메인 메뉴
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
		// 출력 - 거래 로그
		//==========================================
		system("cls"); // 화면 지우기
		PrintLog();

		//==========================================
		// 출력 - 아스키아트(Sales)
		//==========================================
		PrintAsciiArt(static_cast<int>(EMenu::Sell));

		// 출력 - 상점 나가기 선택지
		if (!mIsSpecialShop)
		{// 일반 상점
			FnSetTextColor(EColors::LIGHT_YELLOW);	cout << "[0] 이전으로 돌아가기\n";
		}
		else
		{// 특수 상점
			FnSetTextColor(EColors::LIGHT_YELLOW);	cout << "[0] ○l전으로 돌ㅇrㄱrブl\n";
		}

		//==========================================
		// 판매 불가 (인벤토리가 비어있는 경우)
		//==========================================
		if (player->getInventory().empty())
		{
			PrintSaleNotPossible(player, false);

			//==========================================
			// 회귀 - 메인 메뉴
			//==========================================
			isContinue = false; continue;
		}

		//==========================================
		// 판매 가능 (인벤토리가 채워진 경우)
		//==========================================
		// 출력 - 인벤토리, 소지 골드량
		if (!mIsSpecialShop)
		{// 일반 상점
			DisplayPlayerInventory<EItemRegular>(player, true);
		}
		else
		{// 특수 상점
			DisplayPlayerInventory<EItemSpecial>(player, true);
		}

		// 출력 - 플레이어 소지 금액
		PrintPlayerGold(player, true);

		// 선택 - 판매할 아이템
		string strAsk_SelectItem = "";
		if (!mIsSpecialShop)
		{// 일반 상점
			strAsk_SelectItem = "\"인벤토리 목록\"에서, 판매하려는 아이템 번호를 하나만 선택하세요.\n이전 메뉴로 돌아가려면 숫자 0번을 선택하세요.\n";
		}
		else
		{// 특수 상점
			strAsk_SelectItem = "\"인벤토己l 목록\"øłlnㅓ, 판□Й㈛려는 ㅇr○l템 번호를 ㈛ㄴr口ざ 선택㈛パㅔ요.\n○l전 메뉴로 돌ㅇrㄱr려면 숫ㅈΓ 0번을 선택㈛パㅔ요.\n";
		}
		PrintBySpellingWithColor(strAsk_SelectItem, EColors::YELLOW, ETypingSpeed::FAST);

		//==========================================
		// 매핑 - 키값 & 입력값 
		//==========================================
		map<string, pair<Item*, int>> playerInventory = player->getInventory();
		vector<string> vecChkIdx;
		map<string, pair<Item*, int>>::iterator it;
		for (it = playerInventory.begin(); it != playerInventory.end(); ++it)
		{
			vecChkIdx.push_back(it->first);
		}

		//==========================================
		// 입력(1) - 아이템 번호
		//==========================================
		const string chkedStr_SelectItem = CheckInputValidation(0, playerInventory.size(), player);
		const int digit_SelectItemIdx = stoi(chkedStr_SelectItem);

		// "이전으로 돌아가기" 선택 시
		const int Exit = 0;
		if (Exit == digit_SelectItemIdx)
		{
			//==========================================
			// 회귀 - 메인 메뉴
			//==========================================
			isContinue = false; continue;
		}

		//==========================================
		// 선택한 아이템의 정보 추출
		//==========================================
		// 입력값과 실제 인벤토리 인덱스를 매핑하기 위한 키
		const string strKey = vecChkIdx[digit_SelectItemIdx - 1];			// key-name. 화면상 선택번호는 1번부터이므로 -1 처리함.
		const int quantity = playerInventory.find(strKey)->second.second;	// 수량
		Item* item = playerInventory.find(strKey)->second.first;			// 아이템 타입
		const string strItemDefaultName = item->getName();					// 아이템 기본 이름
		int salePrice = (item->getPrice()) * mSaleRatio;					// 매입가
		int digit_Quantity = 0;												// 실제 판매할 아이템 수량

		const int ONLY_ONE = 1;
		if (ONLY_ONE == quantity)
		{
			//==========================================
			// 선택한 아이템의 수량이 1개뿐인 경우
			//==========================================
			// 선택 - 판매할 아이템
			string strAsk_SellReally = "";
			if (!mIsSpecialShop)
			{// 일반 상점
				strAsk_SellReally = "선택한 아이템은 현재 1개뿐인 아이템입니다. 정말로 판매하시겠습니까?\n";
			}
			else
			{// 특수 상점
				strAsk_SellReally = "선택ㅎŁ ㅇr○l템은 현재 1개뿐인 ㅇr○l템입LI⊂ト. 정말로 판□Й㈛んı겠습LI까?\n";
			}
			PrintBySpellingWithColor(strAsk_SellReally, EColors::LIGHT_RED, ETypingSpeed::FAST);

			if (!IsYes(player))
			{
				//==========================================
				// 회귀 - 메인 메뉴
				//==========================================
				//isContinue = false;
				continue;
			}

			const int ONLY_ONE = 1;	// 판매할 아이템 수량은 1개로 고정
			digit_Quantity = ONLY_ONE;
		}
		else
		{
			//==========================================
			// 입력(2) - 수량
			//==========================================
			// 문장 조립과 출력
			string strAsk_HowMany = "";
			if (!mIsSpecialShop)
			{// 일반 상점
				strAsk_HowMany += "선택한 아이템은 현재 ";
			}
			else
			{// 특수 상점
				strAsk_HowMany += "선택ㅎŁ ㅇr○l템은 현재 ";
			}
			PrintBySpellingWithColor(strAsk_HowMany, EColors::YELLOW, ETypingSpeed::FAST);
			strAsk_HowMany.clear();
			strAsk_HowMany += to_string(quantity);
			PrintBySpellingWithColor(strAsk_HowMany, EColors::LIGHT_YELLOW, ETypingSpeed::FAST);
			strAsk_HowMany.clear();
			if (!mIsSpecialShop)
			{// 일반 상점
				strAsk_HowMany += "개 있습니다.\n판매할 수량을 입력하세요. (1 ~ ";
			}
			else
			{// 특수 상점
				strAsk_HowMany += "개 있습LI⊂ト.\n판□Й할 수량을 입력㈛パㅔ요. (1 ~ ";
			}
			strAsk_HowMany += to_string(quantity);
			strAsk_HowMany += ")\n";
			PrintBySpellingWithColor(strAsk_HowMany, EColors::YELLOW, ETypingSpeed::FAST);

			// 입력
			const string chkedStr_HowMany = CheckInputValidation(1, quantity, player);	// 수량은 1개 이상, 선택한 아이템의 수량 이하로 입력받는다.
			digit_Quantity = stoi(chkedStr_HowMany);
		}

		//==========================================
		// 판매 로직 진행
		//==========================================
		// 매입가 계산 : 1개 단위 매입가에 판매할 아이템 수량이 곱해진다.
		salePrice *= digit_Quantity;

		// 출력 - 판매 성공 문구
		string strBuyResult = "";
		if (!mIsSpecialShop)
		{// 일반 상점
			strBuyResult = "판매 결과: ";
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
			strBuyResult += "개 판매, ";
			PrintBySpellingWithColor(strBuyResult, EColors::YELLOW, ETypingSpeed::FAST);
			strBuyResult.clear();
			strBuyResult += "+";
			strBuyResult += to_string(salePrice);
			strBuyResult += "(G)\n";
			PrintBySpellingWithColor(strBuyResult, EColors::LIGHT_CYAN, ETypingSpeed::FAST);
		}
		else
		{// 특수 상점
			strBuyResult = "판□Й 결과: ";
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
			strBuyResult += "개 판□Й, ";
			PrintBySpellingWithColor(strBuyResult, EColors::YELLOW, ETypingSpeed::FAST);
			strBuyResult.clear();
			strBuyResult += "+";
			strBuyResult += to_string(salePrice);
			strBuyResult += "(G)\n";
			PrintBySpellingWithColor(strBuyResult, EColors::LIGHT_CYAN, ETypingSpeed::FAST);
		}

		// 순서 중요! 실제 아이템 판매 로직 진행 전에 로그 업데이트를 먼저 진행해야 함.
		// 로그 업데이트
		UpdateLogMessage(false, strItemDefaultName, digit_Quantity);

		// 플레이어에게 금액 전달
		player->setGold(player->getGold() + salePrice);

		// 인벤토리 수량 차감
		ReduceItem(player, strKey, digit_Quantity);

		//==========================================
		// 추가 판매 불가 (인벤토리가 비어있는 경우)
		//==========================================
		if (player->getInventory().empty())
		{// 판매 불가
			PrintSaleNotPossible(player, true);

			//==========================================
			// 회귀 - 메인 메뉴
			//==========================================
			isContinue = false; continue;
		}

		//==========================================
		// 추가 판매 가능
		//==========================================
		// 출력 - 인벤토리
		if (!mIsSpecialShop)
		{// 일반 상점
			DisplayPlayerInventory(player, true, true, EItemRegular::END, strKey);
		}
		else
		{// 특수 상점
			DisplayPlayerInventory(player, true, true, EItemSpecial::END, strKey);
		}

		// 출력 - 플레이어 소지 금액
		PrintPlayerGold(player, true);

		// 선택 - Yes/No
		string strAsk_More = "";
		if (!mIsSpecialShop)
		{// 일반 상점
			strAsk_More = "더 판매하시겠습니까?\n";
		}
		else
		{// 특수 상점
			strAsk_More = "て┤ 판□Й㈛んı겠습LI까?\n";
		}
		PrintBySpellingWithColor(strAsk_More, EColors::YELLOW, ETypingSpeed::FAST);

		if (!IsYes(player))
		{
			//==========================================
			// 회귀 -  메인 메뉴
			//==========================================
			isContinue = false; continue;
		}
	}//END-while (isContinue)
}//END-void Shop::SellItem

void Shop::PrintAsciiArt(int _type)
{
	// 일반 상점용
	vector<string> vecAsciiArt;
	vecAsciiArt.clear();
	EColors color = EColors::END;

	// 특수 상점용
	// 벡터는 한 줄씩 출력되므로, 문자열로 처리하여 철자 하나씩 출력하는 방식으로 적용.
	string strAsciiArt = "";

	EMenu type = static_cast<EMenu>(_type);
	switch (type)
	{
	case EMenu::Main:
	{// MainMenu
		if (!mIsSpecialShop)
		{// 일반 상점
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
		{// 특수 상점
			strAsciiArt += "___  ___        _        ___  ___                     ";
			strAsciiArt += "\n|■■\\/■■|       (■)       |■■\\/■■|                     ";
			strAsciiArt += "\n|■■■■■■|  __ _  _  _ __  |■■■■■■|  ___  _ __   _   _  ";
			strAsciiArt += "\n|■|\\/|■| /■■■■||■||■■■■\\ |■|\\/|■| /■■■\|■■■■■\\ |■| |■| ";
			strAsciiArt += "\n|■|  |■||■(_|■||■||■| |■||■|  |■||■■■■/|■| |■||■|_|■| ";
			strAsciiArt += "\n\\■|  |■/ \\■■■■||■||■| |■|\\■|  |■/ \\■■■||■| |■| \\■■■■| ";
		}
	}
	break;
	case EMenu::Buy:
	{// Purchase

		if (!mIsSpecialShop)
		{// 일반 상점
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
		{// 특수 상점
			strAsciiArt += "______                     _                        ";
			strAsciiArt += "\n|■■■■■\\                   |■|                       ";
			strAsciiArt += "\n|■|_/■/ _   _  _ __   ___ |■|__    __ _  ___   ___  ";
			strAsciiArt += "\n|■■■■/ |■| |■||■■■■| /■■■||■■■■\\  /■■■■|/ ■■| /■■■\\ ";
			strAsciiArt += "\n|■|    |■|_|■||■|   |■(__ |■| |■||■(_|■|\\■■ \\|■■■■/ ";
			strAsciiArt += "\n\\■|     \\■■■■||■|   \\■■■■||■| |■| \\■■■■||■■■/ \\■■■| ";
		}
	}
	break;
	case EMenu::Sell:
	{// Sales
		if (!mIsSpecialShop)
		{// 일반 상점
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
		{// 특수 상점
			strAsciiArt += " _____         _                ";
			strAsciiArt += "\n/■■■■■|       |■|               ";
			strAsciiArt += "\n\\■`--.   __ _ |■|  ___  ___    ";
			strAsciiArt += "\n `--.■\\ /■■■■||■| /■■■\\/■■■|  ";
			strAsciiArt += "\n/\\__/■/|■(_|■||■||■■■■/\\■■■\\ ";
			strAsciiArt += "\n\\■■■■/  \\■■■■||■| \\■■■||■■■/ ";
		}
	}
	break;
	case EMenu::Exit:
	{//Caution

		color = EColors::RED;
		if (!mIsSpecialShop)
		{// 일반 상점
			vecAsciiArt = {
			" _____                _    _                ",
			"/■■■■■\\              |■|  (■)               ",
			"|■/  \\/  __ _  _   _ |■|_  _   ___   _ __   ",
			"|■|     /■■■■||■| |■||■■■||■| /■■■\\ |■■■■\\  ",
			"|■\\__/\\|■(_|■||■|_|■||■|_ |■||■(_)■||■| |■| ",
			" \\■■■■/ \\■■■■| \\■■■■| \\■■||■| \\■■■/ |■| |■| "
			};
		}
		else
		{// 특수 상점
			strAsciiArt += " _____                _    _                ";
			strAsciiArt += "\n/■■■■■\\              |■|  (■)               ";
			strAsciiArt += "\n|■/  \\/  __ _  _   _ |■|_  _   ___   _ __   ";
			strAsciiArt += "\n|■|     /■■■■||■| |■||■■■||■| /■■■\\ |■■■■\\  ";
			strAsciiArt += "\n|■\\__/\\|■(_|■||■|_|■||■|_ |■||■(_)■||■| |■| ";
			strAsciiArt += "\n \\■■■■/ \\■■■■| \\■■■■| \\■■||■| \\■■■/ |■| |■| ";
		}
	}
	break;
	case EMenu::END:
		break;
	default:
		break;
	}

	if (!mIsSpecialShop)
	{// 일반 상점
		PrintByLineWithColor(vecAsciiArt, color, ETypingSpeed::SLOW);
	}
	else
	{// 특수 상점
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
	// 출력 - 플레이어 소지 금액
	if (!mIsSpecialShop)
	{// 일반 상점
		strPlayerGold1 = "현재 소지 중인 골드: ";
	}
	else
	{// 특수 상점
		strPlayerGold1 = "현재 소ズl 중인 골드: ";
	}
	PrintBySpellingWithColor(strPlayerGold1, EColors::YELLOW, ETypingSpeed::FAST);

	// 골드 강조
	if (_isEnoughGold)
	{// 충분한 경우
		color = EColors::LIGHT_YELLOW;
	}
	else
	{// 충분하지 않은 경우 - 경고의 느낌으로 RED
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
	{// 일반 상점
		FnSetTextColor(EColors::YELLOW);	cout << "NO (이전으로 돌아가기)\n";
	}
	else
	{// 특수 상점
		FnSetTextColor(EColors::YELLOW);	cout << "NO (○l전으로 돌ㅇrㄱrブl)\n";
	}
	FnSetTextDefault();
}//END-void Shop::PrintYesNoMenu

void Shop::PrintEmptyInventoryMessage()
{
	string str = "";
	if (!mIsSpecialShop)
	{// 일반 상점
		str = "인벤토리가 비어있습니다.\n아이템을 구매하여 인벤토리를 채워보세요.\n";
	}
	else
	{// 특수 상점
		str = "인벤토己lㄱr ㉥ㅣøł있습LI⊂ト.\nㅇr○l템을 구□Й㈛øㅕ 인벤토己l를 채워보パㅔ요.\n";
	}
	PrintBySpellingWithColor(str, EColors::LIGHT_RED, ETypingSpeed::FAST);
}//END-void Shop::PrintEmptyInventoryMessage

void Shop::PrintPurchaseNotPossible(Character* player, bool _isAdditional)
{
	// 출력 - 플레이어 소지 금액
	PrintPlayerGold(player, false);

	string str;
	if (!mIsSpecialShop)
	{// 일반 상점
		if (_isAdditional)
		{// 추가 구매인 경우
			str = "더 이상 구매를 진행할 수 없습니다. 골드가 충분하지 않습니다.\n";
		}
		else
		{// 초기 구매인 경우
			str = "구매할 수 없습니다. 골드가 충분하지 않습니다.\n";
		}
		PrintBySpellingWithColor(str, EColors::LIGHT_RED, ETypingSpeed::FAST);

		const string strAsk = "이전 메뉴로 돌아가려면 숫자 0번을 선택하세요.\n";
		PrintBySpellingWithColor(strAsk, EColors::YELLOW, ETypingSpeed::FAST);
	}
	else
	{// 특수 상점
		if (_isAdditional)
		{// 추가 구매인 경우
			str = "て┤ ○lバ6 구□Й를 진행할 수 없습LI⊂ト. 골드ㄱr 충분㈛ズl 않습LI⊂ト.\n";
		}
		else
		{// 초기 구매인 경우
			str = "구□Й할 수 없습LI⊂ト. 골드ㄱr 충분㈛ズl 않습LI⊂ト.\n";
		}
		PrintBySpellingWithColor(str, EColors::LIGHT_RED, ETypingSpeed::FAST);

		const string strAsk = "○l전 메뉴로 돌ㅇrㄱr려면 숫ㅈΓ 0번을 선택㈛パㅔ요.\n";
		PrintBySpellingWithColor(strAsk, EColors::YELLOW, ETypingSpeed::FAST);
	}

	// 입력 & 유효성 검사 (로직상 반환값 무시 가능)
	const string chkedStr = CheckInputValidation(0, 0, player);
}//END-void Shop::PurchaseNotPossible

void Shop::PrintSaleNotPossible(Character* player, bool _isAdditional)
{
	string str;
	if (!mIsSpecialShop)
	{// 일반 상점
		if (_isAdditional)
		{// 추가 판매인 경우
			str = "더 이상 판매를 진행할 수 없습니다. 인벤토리가 비었습니다.\n";
		}
		else
		{// 초기 판매인 경우
			str = "판매할 수 있는 아이템이 없습니다. 인벤토리가 비어있습니다.\n";
		}
		PrintBySpellingWithColor(str, EColors::LIGHT_RED, ETypingSpeed::FAST);

		const string strAsk = "이전 메뉴로 돌아가려면 숫자 0번을 선택하세요.\n";
		PrintBySpellingWithColor(strAsk, EColors::YELLOW, ETypingSpeed::FAST);
	}
	else
	{// 특수 상점
		if (_isAdditional)
		{// 추가 판매인 경우
			str = "て┤ ○lバ6 판□Й를 진행할 수 없습LI⊂ト. 인벤토己lㄱr ㉥ㅣ었습LI⊂ト.\n";
		}
		else
		{// 초기 판매인 경우
			str = "판□Й할 수 있는 ㅇr○l템○l 없습LI⊂ト. 인벤토己lㄱr ㉥ㅣøł있습LI⊂ト.\n";
		}
		PrintBySpellingWithColor(str, EColors::LIGHT_RED, ETypingSpeed::FAST);

		const string strAsk = "○l전 메뉴로 돌ㅇrㄱr려면 숫ㅈΓ 0번을 선택㈛パㅔ요.\n";
		PrintBySpellingWithColor(strAsk, EColors::YELLOW, ETypingSpeed::FAST);
	}

	// 입력 & 유효성 검사 (로직상 반환값 무시 가능)
	const string chkedStr = CheckInputValidation(0, 0, player);
}//END-void Shop::SaleNotPossible

bool Shop::IsEnoughGoldBuyLowestPrice(Character* player)
{
	bool returnValue = false;

	// 상품 중 최소 가격 찾기
	vector<int> vecPrice;

	if (!mIsSpecialShop)
	{// 일반 상점
		for (const pair<const EItemRegular, unique_ptr<Item>>& pair : mCatalog_Regular)
		{
			vecPrice.push_back(pair.second->getPrice());
		}
	}
	else
	{// 특수 상점
		for (const pair<const EItemSpecial, unique_ptr<Item>>& pair : mCatalog_Special)
		{
			vecPrice.push_back(pair.second->getPrice());
		}
	}

	// 상품 중 최소 가격
	const int minPrice = *std::min_element(vecPrice.begin(), vecPrice.end());
	if (minPrice <= player->getGold())
	{// 골드가 충분한 경우 반환값은 true
		returnValue = true;
	}

	return returnValue;
}//END-bool Shop::IsEnoughGoldBuyLowestPrice

bool Shop::IsYes(Character* player)
{
	bool returnValue = false;

	PrintYesNoMenu();

	// 입력
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
		// 출력 - 거래 로그
		//==========================================
		if (!mIsFirstEntry)
		{
			system("cls"); // 화면 지우기
			PrintLog();
		}

		//==========================================
		// 출력 - 아스키아트(MainMenu)
		//==========================================
		PrintAsciiArt(static_cast<int>(EMenu::Main));

		//==========================================
		// 입력(선택값) - 구매 or 판매
		//==========================================

		if (!mIsSpecialShop)
		{// 일반 상점
			const string strAsk = "원하는 메뉴를 선택하세요.\n";
			PrintBySpellingWithColor(strAsk, EColors::YELLOW, ETypingSpeed::FAST);

			FnSetTextColor(EColors::LIGHT_YELLOW);	cout << "[1] ";
			FnSetTextColor(EColors::YELLOW);		cout << "아이템 구매\n";
			FnSetTextColor(EColors::LIGHT_YELLOW);	cout << "[2] ";
			FnSetTextColor(EColors::YELLOW);		cout << "아이템 판매\n";
			FnSetTextColor(EColors::LIGHT_YELLOW);	cout << "[3] ";
			FnSetTextColor(EColors::YELLOW);		cout << "상점 나가기\n";
			FnSetTextDefault();
		}
		else
		{// 특수 상점
			const string strAsk = "원㈛는 메뉴를 선택㈛パㅔ요.\n";
			PrintBySpellingWithColor(strAsk, EColors::YELLOW, ETypingSpeed::FAST);

			FnSetTextColor(EColors::LIGHT_YELLOW);	cout << "[1] ";
			FnSetTextColor(EColors::YELLOW);		cout << "ㅇr○l템 구□Й\n";
			FnSetTextColor(EColors::LIGHT_YELLOW);	cout << "[2] ";
			FnSetTextColor(EColors::YELLOW);		cout << "ㅇr○l템 판□Й\n";
			FnSetTextColor(EColors::LIGHT_YELLOW);	cout << "[3] ";
			FnSetTextColor(EColors::YELLOW);		cout << "상점 ㄴrㄱrブl\n";
			FnSetTextDefault();
		}

		// 입력
		const string chkedStr = CheckInputValidation(static_cast<int>(EMenu::Buy), static_cast<int>(EMenu::Exit), player);
		const EMenu result = static_cast<EMenu>(stoi(chkedStr));

		mIsFirstEntry = false; // 첫 진입 여부 초기화 (false로 설정)

		//==========================================
		// 분기 - 구매 or 판매
		//==========================================
		// 결과에 따라 흐름을 결정
		switch (result)
		{
		case EMenu::Buy:
			BuyItem(player);
			break;
		case EMenu::Sell:
			SellItem(player);
			break;
		case EMenu::Exit:
			isContinue = !OnExit(player); // true 반환 시 종료
			break;
		default:
			break;
		}
	}
}//END-MainMenu

void Shop::ReduceItem(Character* player, string _strKey, int _quantity)
{
	/*
		Character 클래스의 인벤토리므로
		상점에서 인베토리를 제어하지 않고 캐릭터에게 변경 사항의 정보만 넘겨주고
		인벤토리 변경은 캐릭터가 직접 처리하도록 한다.
		(캐릭터가 인벤토리를 관리하는 책임을 가진다.)
	*/
	//map<string, pair<Item*, int>>& playerInventory = player->getInventory();
	//const int quantity = playerInventory.find(_strKey)->second.second; // 수량

	//const int ONLY_ONE = 1;
	//if (ONLY_ONE == quantity)
	//{// 기존 수량이 1개인 경우
	//	delete playerInventory.find(_strKey)->second.first;	// 먼저 Item*를 해제하고
	//	playerInventory.erase(_strKey);						// 아이템 제거
	//}
	//else
	//{// 기존 수량이 최소 2이상인 경우
	//	playerInventory.find(_strKey)->second.second--;		// 수량 1 감소
	//}

	player->removeItem(_strKey, _quantity);
}//END-void Shop::ReduceItem

string Shop::CheckInputValidation(int _min, int _max, Character* player, bool _isPurchaseMode)
{
	string returnValue = "";
	string strTmp = "";

	while (true)
	{
		cout << "입력: ";
		//cin.ignore();
		getline(std::cin, strTmp);

		if (strTmp.empty())
		{
			FnSetTextColor(EColors::LIGHT_RED);
			if (!mIsSpecialShop)
			{// 일반 상점
				std::cout << "입력값은 비워둘 수 없습니다." << endl;
			}
			else
			{// 특수 상점
				std::cout << "입력값은 ㉥ㅣ워둘 수 없습LI⊂ト." << endl;
			}
			FnSetTextDefault();
			continue;
		}
		if (strTmp.find(' ') != std::string::npos)
		{
			FnSetTextColor(EColors::LIGHT_RED);
			if (!mIsSpecialShop)
			{// 일반 상점
				std::cout << "입력값은 공백을 포함할 수 없습니다." << endl;
			}
			else
			{// 특수 상점
				std::cout << "입력값은 공백을 포ㅎ古할 수 없습LI⊂ト." << endl;
			}
			FnSetTextDefault();
			continue;
		}

		bool isOk = false;
		try
		{
			const int digit = stoi(strTmp); // 예외 발생 가능성 있음
			if ((!_isPurchaseMode) && (_min <= digit) && (digit <= _max))
			{// 일반적인 경우
				isOk = true;
				returnValue = strTmp;

				break;
			}
			else if (_isPurchaseMode)
			{// 구매 모드인 경우
				// 이전으로 돌아가기를 선택한 경우
				const int MIN = 0;
				if (MIN == digit)
				{
					isOk = true;
					returnValue = strTmp;
					break;
				}

				int MAX = -1;
				if (!mIsSpecialShop)
				{// 일반 상점
					MAX = static_cast<int>(EItemRegular::END);
				}
				else
				{// 특수 상점
					MAX = static_cast<int>(EItemSpecial::END);
				}

				if (digit <= MAX)
				{// 아이템 목록의 선택 번호 이내로 입력한 경우

					// 화면상 번호는 시작 번호가 1부터 시작하므로, 실제 매핑될 인덱스와는 1차이가 난다.
					const int idx = digit - 1;

					int price = -1;
					// 선택한 아이템의 가격
					if (!mIsSpecialShop)
					{// 일반 상점
						price = mCatalog_Regular[static_cast<EItemRegular>(idx)]->getPrice();
					}
					else
					{// 특수 상점
						price = mCatalog_Special[static_cast<EItemSpecial>(idx)]->getPrice();
					}

					// 플레이어의 골드
					const int gold = player->getGold();

					if (price <= gold)
					{// 구매 가능한 경우 (선택한 아이템의 가격 <= 플레이어의 골드) 
						isOk = true;
						returnValue = strTmp;
						break;
					}
					// 구매 가능하지 않은 경우는 if문을 타지 못한다. (선택한 아이템의 가격 > 플레이어의 골드)
				}
			}
		}
		catch (const std::invalid_argument& e)
		{// stoi : 숫자가 아닌 문자열 입력 시
			FnSetTextColor(EColors::LIGHT_RED);
			if (!mIsSpecialShop)
			{// 일반 상점
				cout << "숫자 형식이 아닙니다." << endl;
			}
			else
			{// 특수 상점
				cout << "숫ㅈΓ 형식○l ㅇr닙LI⊂ト." << endl;
			}
			FnSetTextDefault();
			continue;
		}
		catch (const std::out_of_range& e)
		{// stoi : 입력 숫자가 int 범위를 초과할 경우
			FnSetTextColor(EColors::LIGHT_RED);
			if (!mIsSpecialShop)
			{// 일반 상점
				cout << "입력값이 너무 큽니다." << endl;
			}
			else
			{// 특수 상점
				cout << "입력값○l 너무 큽LI⊂ト." << endl;
			}
			FnSetTextDefault();
			continue;
		}
		if (!isOk)
		{// 입력값이 숫자여도 유효한 값이 아닌 경우
			FnSetTextColor(EColors::LIGHT_RED);
			if (!mIsSpecialShop)
			{// 일반 상점
				std::cout << "유효한 입력값이 아닙니다." << endl;
			}
			else
			{// 특수 상점
				std::cout << "유효ㅎŁ 입력값○l ㅇr닙LI⊂ト." << endl;
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
	{// 일반 상점
		for (const pair<const EItemRegular, unique_ptr<Item>>& pair : mCatalog_Regular)
		{
			const unique_ptr<Item>& itemPtr = pair.second;
			const string name = itemPtr->getName(); // 아이템 이름을 가져와서 사용

			mPurchaseLog[name] = 0;	// 구매 로그 초기화
			mSalesLog[name] = 0;	// 판매 로그 초기화
		}
	}
	else
	{// 특수 상점
		for (const pair<const EItemSpecial, unique_ptr<Item>>& pair : mCatalog_Special)
		{
			const unique_ptr<Item>& itemPtr = pair.second;
			const string name = itemPtr->getName(); // 아이템 이름을 가져와서 사용

			mPurchaseLog[name] = 0;	// 구매 로그 초기화
			mSalesLog[name] = 0;	// 판매 로그 초기화
		}
	}
}//END-void Shop::CreateLog

void Shop::PrintLog()
{
	// 출력 - 로그 출력 전처리
	FnSetTextColor(EColors::DARK_GRAY);
	string strLog = "History\n";
	strLog += "======================================================================================";
	cout << strLog << endl;
	strLog.clear();

	// 구매 로그 출력
	FnSetTextColor(EColors::LIGHT_GREEN);
	if (!mIsSpecialShop)
	{// 일반 상점
		strLog += "[구매] ";
	}
	else
	{// 특수 상점
		strLog += "[구□Й] ";
	}
	for (const auto& entry : mPurchaseLog)
	{
		strLog += entry.first + ":" + to_string(entry.second) + "/ ";
	}
	strLog.erase(strLog.size() - 2); // 마지막 3글자 제거: "/  "
	cout << strLog << endl;
	strLog.clear();

	// 판매 로그 출력
	FnSetTextColor(EColors::LIGHT_BLUE);
	if (!mIsSpecialShop)
	{// 일반 상점
		strLog += "[판매] ";
	}
	else
	{// 특수 상점
		strLog += "[판□Й] ";
	}
	for (const auto& entry : mSalesLog)
	{
		strLog += entry.first + ":" + to_string(entry.second) + "/ ";
	}
	strLog.erase(strLog.size() - 2); // 마지막 3글자 제거: " /  "
	cout << strLog << endl;
	strLog.clear();

	// 출력 - 로그 출력 후처리
	FnSetTextColor(EColors::DARK_GRAY);
	strLog += "======================================================================================";
	cout << strLog << endl;
	strLog.clear();

	// 기본 색상으로 되돌리기
	FnSetTextDefault();
}//END-void Shop::PrintLog

void Shop::UpdateLogMessage(bool _isPurchase, string _key, int _quantity)
{
	if (_isPurchase)
	{// 구매 로그 업데이트
		mPurchaseLog[_key] += _quantity;
	}
	else
	{// 판매 로그 업데이트
		mSalesLog[_key] += _quantity;
	}
}//END-void Shop::UpdateLogMessage
