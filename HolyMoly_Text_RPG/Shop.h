#pragma once
#include "common.h"

// 템플릿 함수 정의를 위해 헤더 파일에 포함
//-----------------------------------------
#include "Character.h"
#include "Item.h"

#include "HealthPotion.h"
#include "AttackBoost.h"
#include "ExpBook.h"
#include "GoldBar.h"
#include "rottenMeat.h"
#include "HolyWater.h"
#include "Bomb.h"
//-----------------------------------------

enum class EMenu;
enum class EYesNo;

enum class EItemRegular
{
	HealthPotion,	// 0
	AttackBoost,	// 1
	ExpBook,		// 2
	GoldBar,		// 3
	rottenMeat,		// 4
	END
};

enum class EItemSpecial
{
	HolyWater,	// 0
	Bomb,		// 1
	END
};

class Shop
{
public:
	//Shop();
	Shop(Character* player, bool _isSpecial = false);

	// 상점 진입
	void OnEnter(Character* player);

	// 상점 나가기
	bool OnExit(Character* player);

	// 출력 - 판매중인 아이템 목록
	void DisplayItems(Character* player);

	// 구매
	void BuyItem(Character* player);

	// 판매
	void SellItem(Character* player);

private:
	/*
		중복 내용을 함수로 구현
	*/
	// 출력 - 플레이어 인벤토리
	template <typename TEnum>
	void DisplayPlayerInventory(Character* player, bool _isSell, bool _isSuccessDeal = false, TEnum _item = static_cast<TEnum>(-1), string _key = "");

	// 출력 - 아스키 아트
	void PrintAsciiArt(int _type);

	// 출력 - 플레이어 소지 금액
	void PrintPlayerGold(Character* player, bool _isEnoughGold);

	// 출력 - Yes/No
	void PrintYesNoMenu();

	// 출력 - 인벤토리 빈 경우, 문구
	void PrintEmptyInventoryMessage();

	// 출력 - 구매 불가한 경우
	void PrintPurchaseNotPossible(Character* player, bool _isAdditional);

	// 출력 - 판매 불가한 경우
	void PrintSaleNotPossible(Character* player, bool _isAdditional);

	// 구매 가능성 확인 (플레이어 소지 금액이 상품 가격 중 최소 가격보다 적은지 확인)
	bool IsEnoughGoldBuyLowestPrice(Character* player);

	// Yes/No 확인하여 Yes면 true 반환
	bool IsYes(Character* player);

	// 메인메뉴
	void MainMenu(Character* player);

	// 구매 시 플레이어에게 건내 줄 아이템 생성
	template <typename TEnum>
	void RegisterItem(Character* player, TEnum _itemType, int _quantity = 1);

	// 판매 시 아이템 줄이기
	void ReduceItem(Character* player, string _strKey, int _quantity = 1);

	// 입력값 유효성 검사
	string CheckInputValidation(int _min, int _max, Character* player, bool _isPurcahseMode = false);

	// 로그 생성
	void CreateLog();

	// 로그 출력
	void PrintLog();

	// 로그 업데이트
	void UpdateLogMessage(bool _isPurchase, string _key, int _quantity = 1);

private:
	// 판매 중인 아이템 목록
	map<EItemRegular, unique_ptr<Item>>mCatalog_Reugular;
	map<EItemSpecial, unique_ptr<Item>>mCatalog_Special;
	//vector<> availableItems;
	//vector<Item*> availableItems;
	//map<EItem, unique_ptr<Item>>availableItems;

	// 최초 진입 여부 확인
	bool mIsFirstEntry;

	// 특수 상점 여부
	const bool mIsSpecialShop;

	// 할인율
	const float mSaleRatio;

	/*
		unordered_map 을 사용하려다가
		아이템 별로 정렬되야 시각적으로 깔끔한 로그가 될 것 같아서 map 사용
		(아이템 이름을 키로 사용, 거래 수량을 값으로 사용)
	*/
	// 구매 로그
	map<string, int> mPurchaseLog;

	// 판매 로그
	map<string, int> mSalesLog;
};


/*
	이하 템플릿 함수 정의 (템플릿은 cpp에 정의할 수 없음)
*/
// 출력 - 플레이어 인벤토리
template<typename TEnum>
inline void Shop::DisplayPlayerInventory(Character* player, bool _isSell, bool _isSuccessDeal, TEnum _item, string _key)
{
	// TEnum이 enum 타입인지 확인
	static_assert(std::is_enum<TEnum>::value, "TEnum must be an enum type.");

	// 정렬 기준값
	const int SORT_NANE = 36;	// 이름 정렬 기준값
	const int SORT_NUMB = 2;	// 숫자 정렬 기준값

	//==========================================
	// 일반 상점과 특수 상점 구분
	//==========================================
	if constexpr (std::is_same<TEnum, EItemRegular>::value)
	{// EItemRegular 전용 로직
		//==========================================
		// 일반 상점
		//==========================================
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
			const int originalPrice = itemType->getPrice();		// 상품 원가
			const int salePrice = originalPrice * mSaleRatio;	// 매입가

			// 출력
			if (_isSell)
			{// 판매
				if (!_isSuccessDeal)
				{// 판매 전
					// 판매 번호인 인덱스만 강조
					FnSetTextColor(EColors::LIGHT_YELLOW);
					cout << "[" << idx_ItemList++ << "] ";

					FnSetTextColor(EColors::YELLOW);
					string strTmp = "";
					strTmp += "\""; strTmp += name_key; strTmp += "\""; strTmp += "(Type:"; strTmp += itemDefaultName; strTmp += ")";
					cout << left << setw(SORT_NANE) << strTmp;
					cout << " | 수량: " << right << setw(SORT_NUMB) << quantity;
					cout << " | 원가: " << right << setw(SORT_NUMB) << originalPrice << "(G)";
					cout << " | 매입가: " << right << setw(SORT_NUMB) << salePrice << "(G)";
				}
				else
				{// 판매 후
					if (name_key == _key)
					{// 판매한 아이템 강조
						FnSetTextColor(EColors::YELLOW);
						cout << "[" << idx_ItemList++ << "] ";

						FnSetTextColor(EColors::LIGHT_YELLOW);
						string strTmp = "";
						strTmp += "\""; strTmp += name_key; strTmp += "\"";
						strTmp += "(Type:"; strTmp += itemDefaultName; strTmp += ")";
						cout << left << setw(SORT_NANE) << strTmp;

						// 남은 수량 강조
						FnSetTextColor(EColors::LIGHT_CYAN);
						cout << " | 수량: " << right << setw(SORT_NUMB) << quantity;

						FnSetTextColor(EColors::LIGHT_YELLOW);
						cout << " | 원가: " << right << setw(SORT_NUMB) << originalPrice << "(G)";
						cout << " | 매입가: " << right << setw(SORT_NUMB) << salePrice << "(G)";

						isFind = true;
					}
					else
					{// 판매 품목이 아닌 나머지 인벤토리
						// 강조 내용 없음
						FnSetTextColor(EColors::YELLOW);
						cout << "[" << idx_ItemList++ << "] ";
						string strTmp = "";
						strTmp += "\""; strTmp += name_key; strTmp += "\""; strTmp += "(Type:"; strTmp += itemDefaultName; strTmp += ")";
						cout << left << setw(SORT_NANE) << strTmp;
						cout << " | 수량: " << right << setw(SORT_NUMB) << quantity;
						cout << " | 원가: " << right << setw(SORT_NUMB) << originalPrice << "(G)";
						cout << " | 매입가: " << right << setw(SORT_NUMB) << salePrice << "(G)";
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
					string strTmp = "";
					strTmp += "\""; strTmp += name_key; strTmp += "\""; strTmp += "(Type:"; strTmp += itemDefaultName; strTmp += ")";
					cout << left << setw(SORT_NANE) << strTmp;
					cout << " | 수량: " << right << setw(SORT_NUMB) << quantity;
					cout << " | 원가: " << right << setw(SORT_NUMB) << originalPrice << "(G)";
					cout << " | 매입가: " << right << setw(SORT_NUMB) << salePrice << "(G)";
				}
				else
				{// 구매 후
					string name_SelectedItem = mCatalog_Reugular[_item]->getName();

					if (name_key == name_SelectedItem)
					{// 구매한 아이템 강조
						FnSetTextColor(EColors::YELLOW);
						cout << "[" << idx_ItemList++ << "] ";

						FnSetTextColor(EColors::LIGHT_YELLOW);
						string strTmp = "";
						strTmp += "\""; strTmp += name_key; strTmp += "\"";
						strTmp += "(Type:"; strTmp += itemDefaultName; strTmp += ")";
						cout << left << setw(SORT_NANE) << strTmp;

						// 수량 강조
						FnSetTextColor(EColors::LIGHT_CYAN);
						cout << " | 수량: " << right << setw(SORT_NUMB) << quantity;

						FnSetTextColor(EColors::LIGHT_YELLOW);
						cout << " | 원가: " << right << setw(SORT_NUMB) << originalPrice << "(G)";
						cout << " | 매입가: " << right << setw(SORT_NUMB) << salePrice << "(G)";
					}
					else
					{// 구매한 품목이 아닌 나머지 인벤토리
						// 강조 내용 없음
						FnSetTextColor(EColors::YELLOW);
						cout << "[" << idx_ItemList++ << "] ";
						string strTmp = "";
						strTmp += "\""; strTmp += name_key; strTmp += "\""; strTmp += "(Type:"; strTmp += itemDefaultName; strTmp += ")";
						cout << left << setw(SORT_NANE) << strTmp;
						cout << " | 수량: " << right << setw(SORT_NUMB) << quantity;
						cout << " | 원가: " << right << setw(SORT_NUMB) << originalPrice << "(G)";
						cout << " | 매입가: " << right << setw(SORT_NUMB) << salePrice << "(G)";
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
		{// 판매 후, 판매한 아이템이 인벤토리에 없는 경우
			const string strAsk_More = "방금 판매하신 아이템은 더 이상 인벤토리에 없습니다.\n";
			PrintBySpellingWithColor(strAsk_More, EColors::LIGHT_CYAN, ETypingSpeed::FAST);
		}
		FnSetTextDefault();
	}
	else if constexpr (std::is_same<TEnum, EItemSpecial>::value)
	{// EItemSpecial 전용 로직
		//==========================================
		// 특수 상점
		//==========================================
		// 컬러 섞기
		vector<int> colors = {
			static_cast<int>(EColors::GREEN),
			static_cast<int>(EColors::RED),
			static_cast<int>(EColors::LIGHT_CYAN),
			static_cast<int>(EColors::LIGHT_BLUE),
			static_cast<int>(EColors::YELLOW)
		};
		//==========================================
		// 출력 - 아이템 목록 출력 전처리
		//==========================================
		string strLine = "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
		for (size_t i = 0; i < strLine.size(); ++i)
		{// 출력 - 아스키아트 라인
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colors[(i + 3) % colors.size()]);
			cout << strLine[i];
		}
		string str = "인벤토己l 목록:\n";
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
			const int originalPrice = itemType->getPrice();		// 상품 원가
			const int salePrice = originalPrice * mSaleRatio;	// 매입가

			// 출력
			if (_isSell)
			{// 판매
				if (!_isSuccessDeal)
				{// 판매 전
					// 판매 번호인 인덱스만 강조
					FnSetTextColor(EColors::LIGHT_YELLOW);
					cout << "[" << idx_ItemList++ << "] ";

					FnSetTextColor(EColors::YELLOW);
					string strTmp = "";
					strTmp += "\""; strTmp += name_key; strTmp += "\""; strTmp += "(Type:"; strTmp += itemDefaultName; strTmp += ")";
					cout << left << setw(SORT_NANE) << strTmp;
					cout << " | 수량: " << right << setw(SORT_NUMB) << quantity;
					cout << " | 원가: " << right << setw(SORT_NUMB) << originalPrice << "(G)";
					cout << " | 매입가: " << right << setw(SORT_NUMB) << salePrice << "(G)";
				}
				else
				{// 판매 후
					if (name_key == _key)
					{// 판매한 아이템 강조
						FnSetTextColor(EColors::YELLOW);
						cout << "[" << idx_ItemList++ << "] ";

						FnSetTextColor(EColors::LIGHT_YELLOW);
						string strTmp = "";
						strTmp += "\""; strTmp += name_key; strTmp += "\"";
						strTmp += "(Type:"; strTmp += itemDefaultName; strTmp += ")";
						cout << left << setw(SORT_NANE) << strTmp;

						// 남은 수량 강조
						FnSetTextColor(EColors::LIGHT_CYAN);
						cout << " | 수량: " << right << setw(SORT_NUMB) << quantity;

						FnSetTextColor(EColors::LIGHT_YELLOW);
						cout << " | 원가: " << right << setw(SORT_NUMB) << originalPrice << "(G)";
						cout << " | 매입가: " << right << setw(SORT_NUMB) << salePrice << "(G)";

						isFind = true;
					}
					else
					{// 판매 품목이 아닌 나머지 인벤토리
						// 강조 내용 없음
						FnSetTextColor(EColors::YELLOW);
						cout << "[" << idx_ItemList++ << "] ";
						string strTmp = "";
						strTmp += "\""; strTmp += name_key; strTmp += "\""; strTmp += "(Type:"; strTmp += itemDefaultName; strTmp += ")";
						cout << left << setw(SORT_NANE) << strTmp;
						cout << " | 수량: " << right << setw(SORT_NUMB) << quantity;
						cout << " | 원가: " << right << setw(SORT_NUMB) << originalPrice << "(G)";
						cout << " | 매입가: " << right << setw(SORT_NUMB) << salePrice << "(G)";
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
					string strTmp = "";
					strTmp += "\""; strTmp += name_key; strTmp += "\""; strTmp += "(Type:"; strTmp += itemDefaultName; strTmp += ")";
					cout << left << setw(SORT_NANE) << strTmp;
					cout << " | 수량: " << right << setw(SORT_NUMB) << quantity;
					cout << " | 원가: " << right << setw(SORT_NUMB) << originalPrice << "(G)";
					cout << " | 매입가: " << right << setw(SORT_NUMB) << salePrice << "(G)";
				}
				else
				{// 구매 후
					string name_SelectedItem = mCatalog_Special[_item]->getName();

					if (name_key == name_SelectedItem)
					{// 구매한 아이템 강조
						FnSetTextColor(EColors::YELLOW);
						cout << "[" << idx_ItemList++ << "] ";

						FnSetTextColor(EColors::LIGHT_YELLOW);
						string strTmp = "";
						strTmp += "\""; strTmp += name_key; strTmp += "\"";
						strTmp += "(Type:"; strTmp += itemDefaultName; strTmp += ")";
						cout << left << setw(SORT_NANE) << strTmp;

						// 수량 강조
						FnSetTextColor(EColors::LIGHT_CYAN);
						cout << " | 수량: " << right << setw(SORT_NUMB) << quantity;

						FnSetTextColor(EColors::LIGHT_YELLOW);
						cout << " | 원가: " << right << setw(SORT_NUMB) << originalPrice << "(G)";
						cout << " | 매입가: " << right << setw(SORT_NUMB) << salePrice << "(G)";
					}
					else
					{// 구매한 품목이 아닌 나머지 인벤토리
						// 강조 내용 없음
						FnSetTextColor(EColors::YELLOW);
						cout << "[" << idx_ItemList++ << "] ";
						string strTmp = "";
						strTmp += "\""; strTmp += name_key; strTmp += "\""; strTmp += "(Type:"; strTmp += itemDefaultName; strTmp += ")";
						cout << left << setw(SORT_NANE) << strTmp;
						cout << " | 수량: " << right << setw(SORT_NUMB) << quantity;
						cout << " | 원가: " << right << setw(SORT_NUMB) << originalPrice << "(G)";
						cout << " | 매입가: " << right << setw(SORT_NUMB) << salePrice << "(G)";
					}
				}
			}
			cout << endl;
		}
		//==========================================
		// 출력 - 아이템 목록 출력 후처리
		//==========================================
		for (size_t i = 0; i < strLine.size(); ++i)
		{// 출력 - 아스키아트 라인
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colors[(i + 3) % colors.size()]);
			cout << strLine[i];
		}
		if (_isSell && _isSuccessDeal && !isFind)
		{// 판매 후, 판매한 아이템이 인벤토리에 없는 경우
			const string strAsk_More = "방금 판□Й㈛신 ㅇr○l템은 て┤ ○lバ6 인벤토己løłl 없습LI⊂ト.\n";
			PrintBySpellingWithColor(strAsk_More, EColors::LIGHT_CYAN, ETypingSpeed::FAST);
		}
		FnSetTextDefault();
	}
	else
	{// EItemRegular, EItemSpecial 이외의 enum 타입에 대한 처리
		static_assert(false, "Unsupported enum type.");
	}
}

// 구매 시 플레이어에게 건내 줄 아이템 생성
template<typename TEnum>
inline void Shop::RegisterItem(Character* player, TEnum _itemType, int _quantity)
{
	static_assert(std::is_enum<TEnum>::value, "itemType must be an enum");

	if constexpr (std::is_same<TEnum, EItemRegular>::value)
	{// EItemRegular에 대한 처리, 일반 상점 아이템
		switch (_itemType)
		{
		case EItemRegular::HealthPotion:
			player->addItem(new HealthPotion(), _quantity);
			break;
		case EItemRegular::AttackBoost:
			player->addItem(new AttackBoost(), _quantity);
			break;
		case EItemRegular::ExpBook:
			player->addItem(new ExpBook(), _quantity);
			break;
		case EItemRegular::GoldBar:
			player->addItem(new GoldBar(), _quantity);
			break;
		case EItemRegular::rottenMeat:
			player->addItem(new rottenMeat(), _quantity);
			break;
		case EItemRegular::END:
			break;
		default:
			break;
		}
	}
	else if constexpr (std::is_same<TEnum, EItemSpecial>::value)
	{// EItemSpecial에 대한 처리, 특수 상점 아이템
		switch (_itemType)
		{
		case EItemSpecial::HolyWater:
			player->addItem(new HolyWater(), _quantity);
			break;
		case EItemSpecial::Bomb:
			player->addItem(new Bomb(), _quantity);
			break;
		case EItemSpecial::END:
			break;
		default:
			break;
		}
	}
	else
	{// EItemRegular, EItemSpecial 이외의 enum 타입에 대한 처리
		static_assert(false, "Unsupported enum type");
	}
}//END-inline void Shop::RegisterItem
