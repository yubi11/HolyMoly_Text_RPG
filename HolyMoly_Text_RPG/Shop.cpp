#include "Shop.h"

#include "HealthPotion.h"
#include "AttackBoost.h"

#include "Character.h"

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

Shop::Shop()
	:mIsFirstEntry(true), mSaleRatio(0.6f)
{
	int size = static_cast<int>(EItem::END);
	for (int i = 0; i < size; i++)
	{
		EItem key = static_cast<EItem>(i);

		switch (key)
		{
		case EItem::HealthPotion:
			availableItems[key] = std::make_unique<HealthPotion>();
			break;
		case EItem::AttackBoost:
			availableItems[key] = std::make_unique<AttackBoost>();
			break;
		case EItem::END:
			break;
		default:
			break;
		}
	}
}

void Shop::OnEnter(Character* player)
{
	//==========================================
	// 출력 - 아스키아트 Only 최초진입
	//==========================================
	if (mIsFirstEntry)
	{
		// 아스키아트 - Welcome
		vector<string> vecAsciiArt_Welcome;
		vecAsciiArt_Welcome = {
			"  _    _        _                                           ",
			" | |  | |      | |                                          ",
			" | |  | |  ___ | |  ___   ___   _ __ ___    ___             ",
			" | |/\\| | / _ \\| | / __| / _ \\ | '_ ` _ \\  / _ \\       ",
			" \\  /\\  /|  __/| || (__ | (_) || | | | | ||  __/          ",
			"  \\/  \\/  \\___||_| \\___| \\___/ |_| |_| |_| \\___|      ",
			"                                                            ",
			"⠀⢐⣷⢷⡷⣷⢷⡷⡗⠗⠓⠳⢷⣗⠗⠳⣷⡗⠗⢳⣷⠷⠓⠓⠳⢳⡷⡗⠳⠓⠗⠗⣷⡷⣷⢷⡷⣷⡆⠀",
			"⠀⠸⣾⣟⣿⣻⣟⣯⠀⠐⠺⠤⣴⣻⠀⠨⠻⠝⠀⢸⡏⠀⢰⣶⣆⠀⢹⡇⠀⢰⠦⠀⢸⣟⣿⣻⣟⣯⡗⠀ ",
			"⠀⢸⣽⣯⣿⣽⣯⣟⠓⢢⡤⡀⠀⣿⠀⠠⣦⡦⠀⢸⡧⠀⠸⢷⠗⠀⣸⡇⠀⢠⣤⣔⣾⣯⣿⣽⣯⡿⣇⠀ ",
			"⠀⠰⣻⡾⡷⡿⣾⣻⣦⣤⢤⡤⣾⣽⢤⣬⢿⡽⣤⢼⢿⣳⣤⢤⡤⣖⣷⣧⣤⡼⣿⢽⡷⡿⡾⣷⣻⣽⡇⠀",
			"⠀⠠⣦⣦⣦⣦⣦⣦⣦⣦⣦⣦⣦⣦⣦⣦⣦⣦⣦⣦⣦⣦⣦⣦⣦⣦⣦⣦⣦⣦⣦⣦⣦⣦⣦⣦⣦⣦⡆⠀",
			"⠀⠐⣿⣽⣟⣯⣿⣻⡽⢹⣾⣯⣷⢿⣳⣿⠳⣻⡷⣿⣽⣾⢷⡏⢿⡾⣷⢿⣽⣾⡷⢹⢿⡾⣷⢿⡷⣿⡃⠀",
			"⠀⠀⠈⠳⠿⠯⠿⠙⣠⣄⠙⠾⢟⠿⠏⢃⣤⡉⠻⠿⠾⠯⢋⣠⣌⠛⠿⡻⠿⠚⡡⣤⠙⠟⢿⠻⠟⠃⠀⠀ ",
			"⠀⠀⠀⠀⠀⢶⡾⣾⣻⣟⣿⢶⡶⣶⢾⢿⣻⣟⣷⡶⣶⢾⣾⣻⣽⣷⣶⡶⣶⡷⣿⢿⣿⣶⣶⠀⠀⠀⠀⠀  ",
			"⠀⠀⠀⠀⠀⢯⣿⣻⣽⠀⠀⠀⠀⠀⠀⠀⢸⣿⣽⢿⡅⠀⠀⠀⠀⠀⠀⠈⠀⠈⠀⠁⢸⣾⢿⠀⠀⠀⠀⠀    ",
			"⠀⠀⠀⠀⠀⣻⣽⣟⣿⠀⠀⠀⠀⠀⠀⠀⢸⣿⢾⣟⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣟⣿⠀⠀⠀⠀⠀     ",
			"⠀⠀⠀⠀⠀⢾⣻⣿⣽⠀⠀⠀⠀⠀⠀⠀⢸⣿⢾⣟⡇⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡀⡸⣟⣿⠀⠀⠀⠀⠀   ",
			"⠀⠀⠀⠀⠀⣻⣯⣷⣿⠀⠀⠀⠀⠀⠀⠀⢸⣿⣻⣽⣿⣻⣟⣿⣻⣟⣿⣻⣟⣿⣻⣟⣿⣟⣿⠀⠀⠀⠀⠀   ",
			"⠀⠀⠀⠀⠀⣽⣾⢷⣿⣤⣤⣤⣤⣤⣤⣤⣼⡿⣽⡿⣾⢯⣿⣽⣯⣿⣽⣯⣿⣽⣯⣿⣳⣿⣻⠀⠀⠀⠀⠀  ",
			"⠀⠠⣤⣦⣴⣬⣭⣭⣧⣯⣭⣭⣭⣭⣭⣭⣮⣽⣭⣭⣭⣯⣽⣬⣧⣽⣬⣧⣽⣬⣧⣭⣽⣼⣽⣤⣦⣴⡄⠀",
			"⠀⠈⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠑⠉⠉⠉⠉⠁⠀"
		};
		PrintByLineWithColor(vecAsciiArt_Welcome, EColors::LIGHT_CYAN, ETypingSpeed::FAST);
		cout << endl;

		// 출력 - 환영인사
		const string str_Welcome = "상점에 오신 것을 환영합니다!\n아이템을 구매하거나 판매해 보세요!\n\n\n";
		PrintBySpellingWithColor(str_Welcome, EColors::YELLOW, ETypingSpeed::FAST);

		mIsFirstEntry = false;
	}

	// 메인 메뉴
	MainMenu(player);
}//END-void Shop::OnEnter

bool Shop::OnExit(Character* player)
{
	bool returnValue = false;

	//==========================================
	// 출력 - 아스키아트(Caution)
	//==========================================
	PrintAsciiArt(static_cast<int>(EMenu::Exit));
	const string str = "이곳을 벗어나면 바로 전투가 시작됩니다.\n정말 나가시겠습니까?\n";
	PrintBySpellingWithColor(str, EColors::RED, ETypingSpeed::FAST);
	if (IsYes(player))
	{
		returnValue = true;
	}
	FnSetTextDefault();

	return returnValue;
}//END-void Shop::OnExit

void Shop::DisplayItems(Character* player)
{
	//==========================================
	// 출력 - 아이템 목록 출력 전처리
	//==========================================
	FnSetTextColor(EColors::LIGHT_GREEN);
	cout << "======================================================================================\n";
	const string str_ShowItemListBefore = "판매 중인 아이템 목록:\n";
	PrintBySpellingWithColor(str_ShowItemListBefore, EColors::LIGHT_GREEN, ETypingSpeed::FAST);

	//==========================================
	// 출력 - 아이템 목록
	//==========================================
	string str_ItemList = "";

	int idx = 1;
	for (const pair<const EItem, unique_ptr<Item>>& pair : availableItems)
	{
		const EItem& key = pair.first;
		const unique_ptr<Item>& itemPtr = pair.second;

		const int price = itemPtr->getPrice();
		const int playerGold = player->getGold();

		if (price > playerGold)
		{// 비활성화 : 현재 소지 중인 골드로는 구매할 수 없는 경우
			FnSetTextColor(EColors::DARK_GRAY);
			cout << "[" << idx++ << "] ";
		}
		else
		{// 활성화 : 골드가 충분해서 구매할 수 있는 경우
			// 인덱스만 강조
			// 사용자가 번호 입력을 할 때, 강조된 인덱스로 시각적 영향을 주어 선택이 편리하도록 함
			FnSetTextColor(EColors::LIGHT_YELLOW);
			cout << "[" << idx++ << "] ";

			FnSetTextColor(EColors::YELLOW);
		}
		cout << itemPtr->getName() << "(";

		switch (key)
		{
		case EItem::HealthPotion:
			cout << "체력";
			break;
		case EItem::AttackBoost:
			cout << "공격력";
			break;
		case EItem::END:
			break;
		default:
			break;
		}

		cout << " +" << itemPtr->getItemValue() << ")\t: " << itemPtr->getPrice() << " 골드" << endl;
	}

	//==========================================
	// 출력 - 아이템 목록 출력 후처리
	//==========================================
	FnSetTextColor(EColors::LIGHT_GREEN);
	cout << "======================================================================================\n";
	FnSetTextDefault();
}//END - void Shop::DisplayItems;

void Shop::BuyItem(Character* player)
{
	//==========================================
	// 출력 - 아스키아트(Purcahse)
	//==========================================
	PrintAsciiArt(static_cast<int>(EMenu::Buy));

	bool isContinue = true;
	while (isContinue)
	{
		// 출력 - 상점 나가기 선택지
		FnSetTextColor(EColors::LIGHT_YELLOW);	cout << "[0] 이전으로 돌아가기\n";

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
			DisplayPlayerInventory(player, false);
		}
		else
		{// 인벤토리가 비어 있는 경우
			PrintEmptyInventoryMessage();
		}

		// 출력 - 플레이어 소지 금액
		PrintPlayerGold(player, true);

		// 선택 - 구매할 아이템
		const string strAsk_SelectItem = "\"판매 중인 아이템 목록\"에서, 구매하려는 아이템 번호를 하나만 선택하세요.\n이전 메뉴로 돌아가려면 숫자 0번을 선택하세요.\n";
		PrintBySpellingWithColor(strAsk_SelectItem, EColors::YELLOW, ETypingSpeed::FAST);

		// 입력
		const int selection = stoi(CheckInputValidation(0, availableItems.size(), player, true));
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
		const EItem key = static_cast<EItem>(selection - 1); // 화면상 선택번호는 1번부터이므로 -1 처리함.
		const int price = availableItems[key]->getPrice();


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

		// 출력 - 구매 결과
		string strBuyResult = "구매 결과: ";
		PrintBySpellingWithColor(strBuyResult, EColors::LIGHT_YELLOW, ETypingSpeed::FAST);
		strBuyResult.clear();
		strBuyResult += "\"";
		strBuyResult += availableItems[key]->getName();
		strBuyResult += "\"";
		PrintBySpellingWithColor(strBuyResult, EColors::LIGHT_CYAN, ETypingSpeed::FAST);
		strBuyResult.clear();
		strBuyResult += "구매, ";
		PrintBySpellingWithColor(strBuyResult, EColors::YELLOW, ETypingSpeed::FAST);
		strBuyResult.clear();
		strBuyResult += "-";
		strBuyResult += to_string(price);
		strBuyResult += "(G)\n";
		PrintBySpellingWithColor(strBuyResult, EColors::LIGHT_CYAN, ETypingSpeed::FAST);

		// 플레이어에게 아이템 주기
		RegisterItem(player, key);

		// 플레이어 소지 골드 차감
		player->setGold(player->getGold() - price);

		// 출력 - 플레이어 인벤토리
		DisplayPlayerInventory(player, false, true, key);

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
		const string strAsk_More = "더 구매하시겠습니까?\n";
		PrintBySpellingWithColor(strAsk_More, EColors::YELLOW, ETypingSpeed::FAST);

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
	//==========================================
	// 출력 - 아스키아트(Sales)
	//==========================================
	PrintAsciiArt(static_cast<int>(EMenu::Sell));

	bool isContinue = true;
	while (isContinue)
	{
		// 출력 - 상점 나가기 선택지
		FnSetTextColor(EColors::LIGHT_YELLOW);	cout << "[0] 이전으로 돌아가기\n";

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
		DisplayPlayerInventory(player, true);
		PrintPlayerGold(player, true);

		// 선택 - 판매할 아이템
		const string strAsk_SelectItem = "\"인벤토리 목록\"에서, 판매하려는 아이템 번호를 하나만 선택하세요.\n이전 메뉴로 돌아가려면 숫자 0번을 선택하세요.\n";
		PrintBySpellingWithColor(strAsk_SelectItem, EColors::YELLOW, ETypingSpeed::FAST);

		//==========================================
		// 매핑 - 키값 & 입력값 
		//==========================================
		vector<string> vecChkIdx;
		map<string, pair<Item*, int>> playerInventory = player->getInventory();
		map<string, pair<Item*, int>>::iterator it;
		for (it = playerInventory.begin(); it != playerInventory.end(); ++it)
		{
			vecChkIdx.push_back(it->first);
		}

		//==========================================
		// 입력
		//==========================================
		const string chkedStr_SelectItem = CheckInputValidation(0, playerInventory.size(), player);
		const int digit = stoi(chkedStr_SelectItem);

		// "이전으로 돌아가기" 선택 시
		const int Exit = 0;
		if (Exit == digit)
		{
			//==========================================
			// 회귀 - 메인 메뉴
			//==========================================
			isContinue = false; continue;
		}

		//==========================================
		// 판매 로직 진행
		//==========================================
		// 입력값과 실제 인벤토리 인덱스를 매핑하기 위한 키
		const string strKey = vecChkIdx[digit - 1];

		const int quantity = playerInventory.find(strKey)->second.second;	// 수량
		Item* item = playerInventory.find(strKey)->second.first;			// 아이템 타입
		const int salePrice = (item->getPrice()) * mSaleRatio;				// 매입가

		//==========================================
		// 선택한 아이템의 수량이 1개뿐인 경우
		//==========================================
		const int ONLY_ONE = 1;
		if (ONLY_ONE == quantity)
		{
			// 선택 - 판매할 아이템
			const string strAsk_SellReally = "선택한 아이템은 현재 1개뿐인 아이템입니다. 정말로 판매하시겠습니까?\n";
			PrintBySpellingWithColor(strAsk_SellReally, EColors::LIGHT_RED, ETypingSpeed::FAST);

			if (!IsYes(player))
			{
				//==========================================
				// 회귀 - 메인 메뉴
				//==========================================
				//isContinue = false;
				continue;
			}
		}

		//==========================================
		// 판매 성공
		//==========================================
		/*
			입력받는 화면의 아이템 번호값은 1부터 시작하고
			벡터 인덱스는 0부터 시작하므로
			화면의 번호값을 사용자로부터 입력받고 해당 값에서 -1
		*/

		// 출력 - 판매 성공 문구
		string strBuyResult = "판매 결과: ";
		PrintBySpellingWithColor(strBuyResult, EColors::LIGHT_YELLOW, ETypingSpeed::FAST);
		strBuyResult.clear();
		strBuyResult += "\"";
		strBuyResult += strKey;
		strBuyResult += "\"(Type: ";
		strBuyResult += item->getName();
		strBuyResult += ")";
		PrintBySpellingWithColor(strBuyResult, EColors::LIGHT_CYAN, ETypingSpeed::FAST);
		strBuyResult.clear();
		strBuyResult += "판매, ";
		PrintBySpellingWithColor(strBuyResult, EColors::YELLOW, ETypingSpeed::FAST);
		strBuyResult.clear();
		strBuyResult += "+";
		strBuyResult += to_string(salePrice);
		strBuyResult += "(G)\n";
		PrintBySpellingWithColor(strBuyResult, EColors::LIGHT_CYAN, ETypingSpeed::FAST);

		// 플레이어에게 금액 전달
		player->setGold(player->getGold() + salePrice);

		// 인벤토리 수량 차감
		if (ONLY_ONE == quantity)
		{// 기존 수량이 1개인 경우
			ReduceItem(player, strKey);
		}
		else
		{// 기존 수량이 최소 2이상인 경우
			player->getInventory()[strKey].second -= 1;
		}

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
		// 출력 - 인벤토리, 소지 골드량
		DisplayPlayerInventory(player, true, true, EItem::END, strKey);
		PrintPlayerGold(player, true);

		// 선택 - Yes/No
		string strAsk_More = "더 판매하시겠습니까?\n";
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

void Shop::DisplayPlayerInventory(Character* player, bool _isSell, bool _isSuccessDeal, EItem _item, string _key)
{
	//==========================================
	// 출력 - 아이템 목록 출력 전처리
	//==========================================
	FnSetTextColor(EColors::LIGHT_BLUE);
	cout << "======================================================================================\n";
	string str = "인벤토리 목록:\n";
	PrintBySpellingWithColor(str, EColors::LIGHT_BLUE, ETypingSpeed::FAST);

	//==========================================
	// 출력 - 아이템 목록
	//==========================================
	const map<string, pair<Item*, int>> playerInventory = player->getInventory();

	string str_Inventory = "";
	int idx_ItemList = 1;
	bool isFind = false;
	for (const pair<const string, pair<Item*, int>>& entry : playerInventory)
	{
		const string& name_key = entry.first;
		Item* itemType = entry.second.first;
		const int quantity = entry.second.second;

		const string itemDefaultName = itemType->getName();	// 상품 타입 이름
		const int originalPrice = itemType->getPrice();			// 상품 원가
		const int salePrice = originalPrice * mSaleRatio;			// 매입가

		// 출력
		if (_isSell)
		{// 판매
			if (!_isSuccessDeal)
			{// 판매 전

				// 판매 번호인 인덱스만 강조
				FnSetTextColor(EColors::LIGHT_YELLOW);
				cout << "[" << idx_ItemList++ << "] ";

				FnSetTextColor(EColors::YELLOW);
				cout << "\"" << name_key << "\""
					<< "(Type:" << itemDefaultName << ") | 수량: " << quantity << "개 | 원가: " << originalPrice << "(G) | 매입가: " << salePrice << "(G)";
			}
			else
			{// 판매 후
				if (name_key == _key)
				{
					// 인벤토리 출력 반복문 순회 중 이번 회차 아이템의 키값(string: 아이템 이름)과
					// 방금 판매한 아이템 키값과 일치하는 경우
					FnSetTextColor(EColors::YELLOW);
					cout << "[" << idx_ItemList++ << "] ";

					FnSetTextColor(EColors::LIGHT_YELLOW);
					cout << "\"" << name_key << "\""
						<< "(Type:" << itemDefaultName << ") |";

					// 수량 강조
					FnSetTextColor(EColors::LIGHT_CYAN);
					cout << " 수량: " << quantity << "개";

					FnSetTextColor(EColors::LIGHT_YELLOW);
					cout << " | 원가: " << originalPrice << "(G) | 매입가: " << salePrice << "(G)";

					isFind = true;
				}
				else
				{
					// 강조 내용 없음
					FnSetTextColor(EColors::YELLOW);
					cout << "[" << idx_ItemList++ << "] ";
					cout << "\"" << name_key << "\""
						<< "(Type:" << itemDefaultName << ") | 수량: " << quantity
						<< "개 | 원가: " << originalPrice << "(G) | 매입가: " << salePrice << "(G)";
				}
			}
		}
		else
		{// 구매
			if (!_isSuccessDeal)
			{// 구매 전
				// 강조 내용 없음
				FnSetTextColor(EColors::YELLOW);
				cout << "[" << idx_ItemList++ << "] ";
				cout << "\"" << name_key << "\""
					<< "(Type:" << itemDefaultName << ") | 수량: " << quantity
					<< "개 | 원가: " << originalPrice << "(G) | 매입가: " << salePrice << "(G)";
			}
			else
			{// 구매 후
				string name_SelectedItem = availableItems[_item]->getName();
				if (name_key == name_SelectedItem)
				{
					// 인벤토리 출력 반복문 순회 중 이번 회차 아이템의 키값(string: 아이템 이름)과
					// 방금 구매한 아이템 타입의 이름과 일치하는 경우
					FnSetTextColor(EColors::YELLOW);
					cout << "[" << idx_ItemList++ << "] ";

					FnSetTextColor(EColors::LIGHT_YELLOW);
					cout << "\"" << name_key << "\""
						<< "(Type:" << itemDefaultName << ") |";

					// 수량 강조
					FnSetTextColor(EColors::LIGHT_CYAN);
					cout << " 수량: " << quantity << "개";

					FnSetTextColor(EColors::LIGHT_YELLOW);
					cout << " | 원가: " << originalPrice << "(G) | 매입가: " << salePrice << "(G)";
				}
				else
				{
					// 강조 내용 없음
					FnSetTextColor(EColors::YELLOW);
					cout << "[" << idx_ItemList++ << "] ";
					cout << "\"" << name_key << "\""
						<< "(Type:" << itemDefaultName << ") | 수량: " << quantity
						<< "개 | 원가: " << originalPrice << "(G) | 매입가: " << salePrice << "(G)";
				}
			}
		}
		cout << endl;
	}

	//==========================================
	// 출력 - 아이템 목록 출력 후처리
	//==========================================
	FnSetTextColor(EColors::LIGHT_BLUE);
	cout << "======================================================================================\n";

	if (_isSell && _isSuccessDeal && !isFind)
	{
		const string strAsk_More = "방금 판매하신 아이템은 마지막 하나였습니다. 인벤토리에 더 이상 없습니다.\n";
		PrintBySpellingWithColor(strAsk_More, EColors::LIGHT_CYAN, ETypingSpeed::FAST);
	}

	FnSetTextDefault();
}//END-void Shop::DisplayPlayerInventory

void Shop::PrintAsciiArt(int _type)
{
	vector<string> vecAsciiArt;
	vecAsciiArt.clear();
	EColors color = EColors::END;

	EMenu type = static_cast<EMenu>(_type);
	switch (type)
	{
	case EMenu::Main:
	{// MainMenu
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
	break;
	case EMenu::Buy:
	{// Purchase
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
	break;
	case EMenu::Sell:
	{// Sales
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
	break;
	case EMenu::Exit:
	{//Caution
		vecAsciiArt = {
		" _____                _    _                ",
		"/■■■■■\\              |■|  (■)               ",
		"|■/  \\/  __ _  _   _ |■|_  _   ___   _ __   ",
		"|■|     /■■■■||■| |■||■■■||■| /■■■\\ |■■■■\\  ",
		"|■\\__/\\|■(_|■||■|_|■||■|_ |■||■(_)■||■| |■| ",
		" \\■■■■/ \\■■■■| \\■■■■| \\■■||■| \\■■■/ |■| |■| "
		};
		color = EColors::RED;
	}
	break;
	case EMenu::END:
		break;
	default:
		break;
	}
	PrintByLineWithColor(vecAsciiArt, color, ETypingSpeed::SLOW);
	cout << endl;
}//END-void Shop::PrintAsciiArt

void Shop::PrintPlayerGold(Character* player, bool _isEnoughGold)
{
	EColors color = EColors::END;

	// 출력 - 플레이어 소지 금액
	const string strPlayerGold1 = "현재 소지 중인 골드: ";
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
	FnSetTextColor(EColors::YELLOW);		cout << "NO (이전으로 돌아가기)\n";
	FnSetTextDefault();
}//END-void Shop::PrintYesNoMenu

void Shop::PrintEmptyInventoryMessage()
{
	const string str = "인벤토리가 비어있습니다.\n아이템을 구매하여 인벤토리를 채워보세요.\n";
	PrintBySpellingWithColor(str, EColors::LIGHT_RED, ETypingSpeed::FAST);
}//END-void Shop::PrintEmptyInventoryMessage

void Shop::PrintPurchaseNotPossible(Character* player, bool _isAdditional)
{
	// 출력 - 플레이어 소지 금액
	PrintPlayerGold(player, false);

	string str;
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

	// 입력 & 유효성 검사 (로직상 반환값 무시 가능)
	const string chkedStr = CheckInputValidation(0, 0, player);
}//END-void Shop::PurchaseNotPossible

void Shop::PrintSaleNotPossible(Character* player, bool _isAdditional)
{
	string str;
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

	// 입력 & 유효성 검사 (로직상 반환값 무시 가능)
	const string chkedStr = CheckInputValidation(0, 0, player);
}//END-void Shop::SaleNotPossible

bool Shop::IsEnoughGoldBuyLowestPrice(Character* player)
{
	bool returnValue = false;

	// 상품 중 최소 가격 찾기
	vector<int> vecPrice;
	for (const pair<const EItem, unique_ptr<Item>>& pair : availableItems)
	{
		vecPrice.push_back(pair.second->getPrice());
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
		// 출력 - 아스키아트(MainMenu)
		//==========================================
		PrintAsciiArt(static_cast<int>(EMenu::Main));

		//==========================================
		// 입력(선택값) - 구매 or 판매
		//==========================================
		const string strAsk = "원하는 메뉴를 선택하세요.\n";
		PrintBySpellingWithColor(strAsk, EColors::YELLOW, ETypingSpeed::FAST);

		FnSetTextColor(EColors::LIGHT_YELLOW);	cout << "[1] ";
		FnSetTextColor(EColors::YELLOW);		cout << "아이템 구매\n";
		FnSetTextColor(EColors::LIGHT_YELLOW);	cout << "[2] ";
		FnSetTextColor(EColors::YELLOW);		cout << "아이템 판매\n";
		FnSetTextColor(EColors::LIGHT_YELLOW);	cout << "[3] ";
		FnSetTextColor(EColors::YELLOW);		cout << "상점 나가기\n";
		FnSetTextDefault();

		// 입력
		const string chkedStr = CheckInputValidation(static_cast<int>(EMenu::Buy), static_cast<int>(EMenu::Exit), player);
		const EMenu result = static_cast<EMenu>(stoi(chkedStr));

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

void Shop::RegisterItem(Character* player, EItem _itemType)
{
	const int AddQuantity = 1; // 아이템 수량 증가값은 1개로 고정
	const string itemName = availableItems[_itemType]->getName();
	map<string, pair<Item*, int>>& playerInventory = player->getInventory();
	const map<string, pair<Item*, int>>::iterator it = playerInventory.find(itemName);

	if (it != playerInventory.end())
	{// 아이템이 이미 존재하는 경우
		playerInventory.find(itemName)->second.second++; // 수량 1 증가
	}
	else
	{// 아이템이 존재하지 않는 경우
		switch (_itemType)
		{
		case EItem::HealthPotion:
		{
			playerInventory.emplace(itemName, make_pair(new HealthPotion(), AddQuantity));
		}
		break;
		case EItem::AttackBoost:
		{
			playerInventory.emplace(itemName, make_pair(new AttackBoost(), AddQuantity));
		}
		break;
		default:
			break;
		}
	}
}//void Shop::RegisterItem

void Shop::ReduceItem(Character* player, string _strKey)
{
	map<string, pair<Item*, int>>& playerInventory = player->getInventory();
	const int quantity = playerInventory.find(_strKey)->second.second; // 수량

	const int ONLY_ONE = 1;
	if (ONLY_ONE == quantity)
	{// 기존 수량이 1개인 경우
		delete playerInventory.find(_strKey)->second.first;	// 먼저 Item*를 해제하고
		playerInventory.erase(_strKey);						// 아이템 제거
	}
	else
	{// 기존 수량이 최소 2이상인 경우
		playerInventory.find(_strKey)->second.second--;		// 수량 1 감소
	}
}//END-void Shop::ReduceItem

string Shop::CheckInputValidation(int _min, int _max, Character* player, bool _isPurcahseMode)
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
			std::cout << "입력값은 비워둘 수 없습니다." << endl;
			FnSetTextDefault();
			continue;
		}
		if (strTmp.find(' ') != std::string::npos)
		{
			FnSetTextColor(EColors::LIGHT_RED);
			std::cout << "입력값은 공백을 포함할 수 없습니다." << endl;
			FnSetTextDefault();
			continue;
		}

		bool isOk = false;
		try
		{
			const int digit = stoi(strTmp); // 예외 발생 가능성 있음
			if ((!_isPurcahseMode) && (_min <= digit) && (digit <= _max))
			{// 일반적인 경우
				isOk = true;
				returnValue = strTmp;

				break;
			}
			else if (_isPurcahseMode)
			{// 구매 모드인 경우
				// 이전으로 돌아가기를 선택한 경우
				const int MIN = 0;
				if (MIN == digit)
				{
					isOk = true;
					returnValue = strTmp;
					break;
				}

				const int MAX = static_cast<int>(EItem::END);
				if (digit <= MAX)
				{// 아이템 목록의 선택 번호 이내로 입력한 경우

					// 화면상 번호는 시작 번호가 1부터 시작하므로, 실제 매핑될 인덱스와는 1차이가 난다.
					const int idx = digit - 1;

					// 선택한 아이템의 가격
					const int price = availableItems[static_cast<EItem>(idx)]->getPrice();

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
			cout << "숫자 형식이 아닙니다." << endl;
			FnSetTextDefault();
			continue;
		}
		catch (const std::out_of_range& e)
		{// stoi : 입력 숫자가 int 범위를 초과할 경우
			FnSetTextColor(EColors::LIGHT_RED);
			cout << "입력값이 너무 큽니다." << endl;
			FnSetTextDefault();
			continue;
		}
		if (!isOk)
		{// 입력값이 숫자여도 유효한 값이 아닌 경우
			FnSetTextColor(EColors::LIGHT_RED);
			std::cout << "유효한 입력값이 아닙니다." << endl;
			FnSetTextDefault();
			continue;
		}
	}
	cout << endl;
	return returnValue;
}//END-string Shop::CheckInputValidation
