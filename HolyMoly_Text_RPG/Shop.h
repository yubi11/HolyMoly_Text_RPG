#pragma once
#include "common.h"

// ���ø� �Լ� ���Ǹ� ���� ���� ���Ͽ� ����
//-----------------------------------------
#include "Character.h"
#include "Item.h"

#include "HealthPotion.h"
#include "AttackBoost.h"
#include "ExpBook.h"
#include "GoldBar.h"
#include "rottenMeat.h"
#include "HolyWater.h"
#include "ChaosOrb.h"

template<typename T>
struct always_false : std::false_type {};
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
	ChaosOrb,	// 1
	END
};

class Shop
{
public:
	//Shop();
	Shop(Character* player, bool _isSpecial = false);

	// ���� ����
	void OnEnter(Character* player);

	// ���� ������
	bool OnExit(Character* player);

	// ���� - �Ǹ����� ������ ����
	void DisplayItems(Character* player);

	// ����
	void BuyItem(Character* player);

	// �Ǹ�
	void SellItem(Character* player);

private:
	/*
		�ߺ� ������ �Լ��� ����
	*/
	// ���� - �÷��̾� �κ��丮
	template <typename TEnum>
	void DisplayPlayerInventory(Character* player, bool _isSell, bool _isSuccessDeal = false, TEnum _item = static_cast<TEnum>(-1), string _key = "");

	// ���� - �ƽ�Ű ��Ʈ
	void PrintAsciiArt(int _type);

	// ���� - �÷��̾� ���� �ݾ�
	void PrintPlayerGold(Character* player, bool _isEnoughGold);

	// ���� - Yes/No
	void PrintYesNoMenu();

	// ���� - �κ��丮 �� ����, ����
	void PrintEmptyInventoryMessage();

	// ���� - ���� �Ұ��� ����
	void PrintPurchaseNotPossible(Character* player, bool _isAdditional);

	// ���� - �Ǹ� �Ұ��� ����
	void PrintSaleNotPossible(Character* player, bool _isAdditional);

	// ���� ���ɼ� Ȯ�� (�÷��̾� ���� �ݾ��� ��ǰ ���� �� �ּ� ���ݺ��� ������ Ȯ��)
	bool IsEnoughGoldBuyLowestPrice(Character* player);

	// Yes/No Ȯ���Ͽ� Yes�� true ��ȯ
	bool IsYes(Character* player);

	// ���θ޴�
	void MainMenu(Character* player);

	// ���� �� �÷��̾�� �ǳ� �� ������ ����
	template <typename TEnum>
	void RegisterItem(Character* player, TEnum _itemType, int _quantity = 1);

	// �Ǹ� �� ������ ���̱�
	void ReduceItem(Character* player, string _strKey, int _quantity = 1);


	// 입력값 유효성 검사
	string CheckInputValidation(int _min, int _max, Character* player, bool _isPurchaseMode = false);

	// �Է°� ��ȿ�� �˻�
	string CheckInputValidation(int _min, int _max, Character* player, bool _isPurcahseMode = false);


	// �α� ����
	void CreateLog();

	// �α� ����
	void PrintLog();

	// �α� ������Ʈ
	void UpdateLogMessage(bool _isPurchase, string _key, int _quantity = 1);

private:

	// 판매 중인 아이템 목록
	map<EItemRegular, unique_ptr<Item>>mCatalog_Regular;

	// �Ǹ� ���� ������ ����
	map<EItemRegular, unique_ptr<Item>>mCatalog_Reugular;

	map<EItemSpecial, unique_ptr<Item>>mCatalog_Special;
	//vector<> availableItems;
	//vector<Item*> availableItems;
	//map<EItem, unique_ptr<Item>>availableItems;

	// ���� ���� ���� Ȯ��
	bool mIsFirstEntry;

	// Ư�� ���� ����
	const bool mIsSpecialShop;

	// ������
	const float mSaleRatio;

	/*
		unordered_map �� �����Ϸ��ٰ�
		������ ���� ���ĵǾ� �ð������� ������ �αװ� �� �� ���Ƽ� map ����
		(������ �̸��� Ű�� ����, �ŷ� ������ ������ ����)
	*/
	// ���� �α�
	map<string, int> mPurchaseLog;

	// �Ǹ� �α�
	map<string, int> mSalesLog;
};


/*
	���� ���ø� �Լ� ���� (���ø��� cpp�� ������ �� ����)
*/
// ���� - �÷��̾� �κ��丮
template<typename TEnum>
inline void Shop::DisplayPlayerInventory(Character* player, bool _isSell, bool _isSuccessDeal, TEnum _item, string _key)
{
	// TEnum�� enum Ÿ������ Ȯ��
	static_assert(std::is_enum<TEnum>::value, "TEnum must be an enum type.");


	// 정렬 기준값
	const int SORT_NANE = 36;	// 이름 정렬 기준값
	const int SORT_NUMB_2 = 2;	// 숫자 정렬 기준값
	const int SORT_NUMB_3 = 3;	// 숫자 정렬 기준값

	// ���� ���ذ�
	const int SORT_NANE = 36;	// �̸� ���� ���ذ�
	const int SORT_NUMB = 2;	// ���� ���� ���ذ�


	//==========================================
	// �Ϲ� ������ Ư�� ���� ����
	//==========================================
	if constexpr (std::is_same<TEnum, EItemRegular>::value)
	{// EItemRegular ���� ����
		//==========================================
		// �Ϲ� ����
		//==========================================
		//==========================================
		// ���� - ������ ���� ���� ��ó��
		//==========================================
		FnSetTextColor(EColors::LIGHT_BLUE);
		cout << "======================================================================================\n";
		string str = "�κ��丮 ����:\n";
		PrintBySpellingWithColor(str, EColors::LIGHT_BLUE, ETypingSpeed::FAST);

		//==========================================
		// ���� - ������ ����
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

			const string itemDefaultName = itemType->getName();	// ��ǰ Ÿ�� �̸�
			const int originalPrice = itemType->getPrice();		// ��ǰ ����
			const int salePrice = originalPrice * mSaleRatio;	// ���԰�

			// ����
			if (_isSell)
			{// �Ǹ�
				if (!_isSuccessDeal)
				{// �Ǹ� ��
					// �Ǹ� ��ȣ�� �ε����� ����
					FnSetTextColor(EColors::LIGHT_YELLOW);
					cout << "[" << idx_ItemList++ << "] ";

					FnSetTextColor(EColors::YELLOW);
					string strTmp = "";
					strTmp += "\""; strTmp += name_key; strTmp += "\""; strTmp += "(Type:"; strTmp += itemDefaultName; strTmp += ")";
					cout << left << setw(SORT_NANE) << strTmp;

					cout << " | 수량: " << right << setw(SORT_NUMB_2) << quantity;
					cout << " | 원가: " << right << setw(SORT_NUMB_3) << originalPrice << "(G)";
					cout << " | 매입가: " << right << setw(SORT_NUMB_2) << salePrice << "(G)";

					cout << " | ����: " << right << setw(SORT_NUMB) << quantity;
					cout << " | ����: " << right << setw(SORT_NUMB) << originalPrice << "(G)";
					cout << " | ���԰�: " << right << setw(SORT_NUMB) << salePrice << "(G)";

				}
				else
				{// �Ǹ� ��
					if (name_key == _key)
					{// �Ǹ��� ������ ����
						FnSetTextColor(EColors::YELLOW);
						cout << "[" << idx_ItemList++ << "] ";

						FnSetTextColor(EColors::LIGHT_YELLOW);
						string strTmp = "";
						strTmp += "\""; strTmp += name_key; strTmp += "\"";
						strTmp += "(Type:"; strTmp += itemDefaultName; strTmp += ")";
						cout << left << setw(SORT_NANE) << strTmp;

						// ���� ���� ����
						FnSetTextColor(EColors::LIGHT_CYAN);

						cout << " | 수량: " << right << setw(SORT_NUMB_2) << quantity;

						FnSetTextColor(EColors::LIGHT_YELLOW);
						cout << " | 원가: " << right << setw(SORT_NUMB_3) << originalPrice << "(G)";
						cout << " | 매입가: " << right << setw(SORT_NUMB_2) << salePrice << "(G)";

						cout << " | ����: " << right << setw(SORT_NUMB) << quantity;

						FnSetTextColor(EColors::LIGHT_YELLOW);
						cout << " | ����: " << right << setw(SORT_NUMB) << originalPrice << "(G)";
						cout << " | ���԰�: " << right << setw(SORT_NUMB) << salePrice << "(G)";


						isFind = true;
					}
					else
					{// �Ǹ� ǰ���� �ƴ� ������ �κ��丮
						// ���� ���� ����
						FnSetTextColor(EColors::YELLOW);
						cout << "[" << idx_ItemList++ << "] ";
						string strTmp = "";
						strTmp += "\""; strTmp += name_key; strTmp += "\""; strTmp += "(Type:"; strTmp += itemDefaultName; strTmp += ")";
						cout << left << setw(SORT_NANE) << strTmp;

						cout << " | 수량: " << right << setw(SORT_NUMB_2) << quantity;
						cout << " | 원가: " << right << setw(SORT_NUMB_3) << originalPrice << "(G)";
						cout << " | 매입가: " << right << setw(SORT_NUMB_2) << salePrice << "(G)";

						cout << " | ����: " << right << setw(SORT_NUMB) << quantity;
						cout << " | ����: " << right << setw(SORT_NUMB) << originalPrice << "(G)";
						cout << " | ���԰�: " << right << setw(SORT_NUMB) << salePrice << "(G)";

					}
				}
			}
			else
			{// ����
				if (!_isSuccessDeal)
				{// ���� ��
					// ���� ���� ����
					FnSetTextColor(EColors::YELLOW);
					cout << "[" << idx_ItemList++ << "] ";
					string strTmp = "";
					strTmp += "\""; strTmp += name_key; strTmp += "\""; strTmp += "(Type:"; strTmp += itemDefaultName; strTmp += ")";
					cout << left << setw(SORT_NANE) << strTmp;

					cout << " | 수량: " << right << setw(SORT_NUMB_2) << quantity;
					cout << " | 원가: " << right << setw(SORT_NUMB_3) << originalPrice << "(G)";
					cout << " | 매입가: " << right << setw(SORT_NUMB_2) << salePrice << "(G)";
				}
				else
				{// 구매 후
					string name_SelectedItem = mCatalog_Regular[_item]->getName();

					cout << " | ����: " << right << setw(SORT_NUMB) << quantity;
					cout << " | ����: " << right << setw(SORT_NUMB) << originalPrice << "(G)";
					cout << " | ���԰�: " << right << setw(SORT_NUMB) << salePrice << "(G)";
				}
				else
				{// ���� ��
					string name_SelectedItem = mCatalog_Reugular[_item]->getName();


					if (name_key == name_SelectedItem)
					{// ������ ������ ����
						FnSetTextColor(EColors::YELLOW);
						cout << "[" << idx_ItemList++ << "] ";

						FnSetTextColor(EColors::LIGHT_YELLOW);
						string strTmp = "";
						strTmp += "\""; strTmp += name_key; strTmp += "\"";
						strTmp += "(Type:"; strTmp += itemDefaultName; strTmp += ")";
						cout << left << setw(SORT_NANE) << strTmp;

						// ���� ����
						FnSetTextColor(EColors::LIGHT_CYAN);

						cout << " | 수량: " << right << setw(SORT_NUMB_2) << quantity;

						FnSetTextColor(EColors::LIGHT_YELLOW);
						cout << " | 원가: " << right << setw(SORT_NUMB_3) << originalPrice << "(G)";
						cout << " | 매입가: " << right << setw(SORT_NUMB_2) << salePrice << "(G)";

						cout << " | ����: " << right << setw(SORT_NUMB) << quantity;

						FnSetTextColor(EColors::LIGHT_YELLOW);
						cout << " | ����: " << right << setw(SORT_NUMB) << originalPrice << "(G)";
						cout << " | ���԰�: " << right << setw(SORT_NUMB) << salePrice << "(G)";

					}
					else
					{// ������ ǰ���� �ƴ� ������ �κ��丮
						// ���� ���� ����
						FnSetTextColor(EColors::YELLOW);
						cout << "[" << idx_ItemList++ << "] ";
						string strTmp = "";
						strTmp += "\""; strTmp += name_key; strTmp += "\""; strTmp += "(Type:"; strTmp += itemDefaultName; strTmp += ")";
						cout << left << setw(SORT_NANE) << strTmp;

						cout << " | 수량: " << right << setw(SORT_NUMB_2) << quantity;
						cout << " | 원가: " << right << setw(SORT_NUMB_3) << originalPrice << "(G)";
						cout << " | 매입가: " << right << setw(SORT_NUMB_2) << salePrice << "(G)";

						cout << " | ����: " << right << setw(SORT_NUMB) << quantity;
						cout << " | ����: " << right << setw(SORT_NUMB) << originalPrice << "(G)";
						cout << " | ���԰�: " << right << setw(SORT_NUMB) << salePrice << "(G)";

					}
				}
			}
			cout << endl;
		}
		//==========================================
		// ���� - ������ ���� ���� ��ó��
		//==========================================
		FnSetTextColor(EColors::LIGHT_BLUE);
		cout << "======================================================================================\n";
		if (_isSell && _isSuccessDeal && !isFind)
		{// �Ǹ� ��, �Ǹ��� �������� �κ��丮�� ���� ����
			const string strAsk_More = "���� �Ǹ��Ͻ� �������� �� �̻� �κ��丮�� �����ϴ�.\n";
			PrintBySpellingWithColor(strAsk_More, EColors::LIGHT_CYAN, ETypingSpeed::FAST);
		}
		FnSetTextDefault();
	}
	else if constexpr (std::is_same<TEnum, EItemSpecial>::value)
	{// EItemSpecial ���� ����
		//==========================================
		// Ư�� ����
		//==========================================
		// �÷� ����
		vector<int> colors = {
			static_cast<int>(EColors::GREEN),
			static_cast<int>(EColors::RED),
			static_cast<int>(EColors::LIGHT_CYAN),
			static_cast<int>(EColors::LIGHT_BLUE),
			static_cast<int>(EColors::YELLOW)
		};
		//==========================================
		// ���� - ������ ���� ���� ��ó��
		//==========================================
		string strLine = "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
		for (size_t i = 0; i < strLine.size(); ++i)

		{// 출력 - 아스키아트 라인
			const int colorIndex = (i + 3) % colors.size();
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colors[colorIndex]);

		{// ���� - �ƽ�Ű��Ʈ ����
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colors[(i + 3) % colors.size()]);

			cout << strLine[i];
		}
		string str = "�κ�����l ����:\n";
		PrintBySpellingWithColor(str, EColors::LIGHT_BLUE, ETypingSpeed::FAST);

		//==========================================
		// ���� - ������ ����
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

			const string itemDefaultName = itemType->getName();	// ��ǰ Ÿ�� �̸�
			const int originalPrice = itemType->getPrice();		// ��ǰ ����
			const int salePrice = originalPrice * mSaleRatio;	// ���԰�

			// ����
			if (_isSell)
			{// �Ǹ�
				if (!_isSuccessDeal)
				{// �Ǹ� ��
					// �Ǹ� ��ȣ�� �ε����� ����
					FnSetTextColor(EColors::LIGHT_YELLOW);
					cout << "[" << idx_ItemList++ << "] ";

					FnSetTextColor(EColors::YELLOW);
					string strTmp = "";
					strTmp += "\""; strTmp += name_key; strTmp += "\""; strTmp += "(Type:"; strTmp += itemDefaultName; strTmp += ")";
					cout << left << setw(SORT_NANE) << strTmp;

					cout << " | 수량: " << right << setw(SORT_NUMB_2) << quantity;
					cout << " | 원가: " << right << setw(SORT_NUMB_3) << originalPrice << "(G)";
					cout << " | 매입가: " << right << setw(SORT_NUMB_2) << salePrice << "(G)";

					cout << " | ����: " << right << setw(SORT_NUMB) << quantity;
					cout << " | ����: " << right << setw(SORT_NUMB) << originalPrice << "(G)";
					cout << " | ���԰�: " << right << setw(SORT_NUMB) << salePrice << "(G)";

				}
				else
				{// �Ǹ� ��
					if (name_key == _key)
					{// �Ǹ��� ������ ����
						FnSetTextColor(EColors::YELLOW);
						cout << "[" << idx_ItemList++ << "] ";

						FnSetTextColor(EColors::LIGHT_YELLOW);
						string strTmp = "";
						strTmp += "\""; strTmp += name_key; strTmp += "\"";
						strTmp += "(Type:"; strTmp += itemDefaultName; strTmp += ")";
						cout << left << setw(SORT_NANE) << strTmp;

						// ���� ���� ����
						FnSetTextColor(EColors::LIGHT_CYAN);

						cout << " | 수량: " << right << setw(SORT_NUMB_2) << quantity;

						FnSetTextColor(EColors::LIGHT_YELLOW);
						cout << " | 원가: " << right << setw(SORT_NUMB_3) << originalPrice << "(G)";
						cout << " | 매입가: " << right << setw(SORT_NUMB_2) << salePrice << "(G)";

						cout << " | ����: " << right << setw(SORT_NUMB) << quantity;

						FnSetTextColor(EColors::LIGHT_YELLOW);
						cout << " | ����: " << right << setw(SORT_NUMB) << originalPrice << "(G)";
						cout << " | ���԰�: " << right << setw(SORT_NUMB) << salePrice << "(G)";


						isFind = true;
					}
					else
					{// �Ǹ� ǰ���� �ƴ� ������ �κ��丮
						// ���� ���� ����
						FnSetTextColor(EColors::YELLOW);
						cout << "[" << idx_ItemList++ << "] ";
						string strTmp = "";
						strTmp += "\""; strTmp += name_key; strTmp += "\""; strTmp += "(Type:"; strTmp += itemDefaultName; strTmp += ")";
						cout << left << setw(SORT_NANE) << strTmp;

						cout << " | 수량: " << right << setw(SORT_NUMB_2) << quantity;
						cout << " | 원가: " << right << setw(SORT_NUMB_3) << originalPrice << "(G)";
						cout << " | 매입가: " << right << setw(SORT_NUMB_2) << salePrice << "(G)";
						cout << " | ����: " << right << setw(SORT_NUMB) << quantity;
						cout << " | ����: " << right << setw(SORT_NUMB) << originalPrice << "(G)";
						cout << " | ���԰�: " << right << setw(SORT_NUMB) << salePrice << "(G)";

					}
				}
			}
			else
			{// ����
				if (!_isSuccessDeal)
				{// ���� ��
					// ���� ���� ����
					FnSetTextColor(EColors::YELLOW);
					cout << "[" << idx_ItemList++ << "] ";
					string strTmp = "";
					strTmp += "\""; strTmp += name_key; strTmp += "\""; strTmp += "(Type:"; strTmp += itemDefaultName; strTmp += ")";
					cout << left << setw(SORT_NANE) << strTmp;

					cout << " | 수량: " << right << setw(SORT_NUMB_2) << quantity;
					cout << " | 원가: " << right << setw(SORT_NUMB_3) << originalPrice << "(G)";
					cout << " | 매입가: " << right << setw(SORT_NUMB_2) << salePrice << "(G)";

					cout << " | ����: " << right << setw(SORT_NUMB) << quantity;
					cout << " | ����: " << right << setw(SORT_NUMB) << originalPrice << "(G)";
					cout << " | ���԰�: " << right << setw(SORT_NUMB) << salePrice << "(G)";

				}
				else
				{// ���� ��
					string name_SelectedItem = mCatalog_Special[_item]->getName();

					if (name_key == name_SelectedItem)
					{// ������ ������ ����
						FnSetTextColor(EColors::YELLOW);
						cout << "[" << idx_ItemList++ << "] ";

						FnSetTextColor(EColors::LIGHT_YELLOW);
						string strTmp = "";
						strTmp += "\""; strTmp += name_key; strTmp += "\"";
						strTmp += "(Type:"; strTmp += itemDefaultName; strTmp += ")";
						cout << left << setw(SORT_NANE) << strTmp;

						// ���� ����
						FnSetTextColor(EColors::LIGHT_CYAN);

						cout << " | 수량: " << right << setw(SORT_NUMB_2) << quantity;

						FnSetTextColor(EColors::LIGHT_YELLOW);
						cout << " | 원가: " << right << setw(SORT_NUMB_3) << originalPrice << "(G)";
						cout << " | 매입가: " << right << setw(SORT_NUMB_2) << salePrice << "(G)";

						cout << " | ����: " << right << setw(SORT_NUMB) << quantity;

						FnSetTextColor(EColors::LIGHT_YELLOW);
						cout << " | ����: " << right << setw(SORT_NUMB) << originalPrice << "(G)";
						cout << " | ���԰�: " << right << setw(SORT_NUMB) << salePrice << "(G)";

					}
					else
					{// ������ ǰ���� �ƴ� ������ �κ��丮
						// ���� ���� ����
						FnSetTextColor(EColors::YELLOW);
						cout << "[" << idx_ItemList++ << "] ";
						string strTmp = "";
						strTmp += "\""; strTmp += name_key; strTmp += "\""; strTmp += "(Type:"; strTmp += itemDefaultName; strTmp += ")";
						cout << left << setw(SORT_NANE) << strTmp;

						cout << " | 수량: " << right << setw(SORT_NUMB_2) << quantity;
						cout << " | 원가: " << right << setw(SORT_NUMB_3) << originalPrice << "(G)";
						cout << " | 매입가: " << right << setw(SORT_NUMB_2) << salePrice << "(G)";

						cout << " | ����: " << right << setw(SORT_NUMB) << quantity;
						cout << " | ����: " << right << setw(SORT_NUMB) << originalPrice << "(G)";
						cout << " | ���԰�: " << right << setw(SORT_NUMB) << salePrice << "(G)";

					}
				}
			}
			cout << endl;
		}
		//==========================================
		// ���� - ������ ���� ���� ��ó��
		//==========================================
		for (size_t i = 0; i < strLine.size(); ++i)
		{// ���� - �ƽ�Ű��Ʈ ����
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colors[(i + 3) % colors.size()]);
			cout << strLine[i];
		}
		if (_isSell && _isSuccessDeal && !isFind)
		{// �Ǹ� ��, �Ǹ��� �������� �κ��丮�� ���� ����
			const string strAsk_More = "���� �ǡଫ�̽� ��r��l���� �Ʀ� ��l��6 �κ�����l����l ����LI����.\n";
			PrintBySpellingWithColor(strAsk_More, EColors::LIGHT_CYAN, ETypingSpeed::FAST);
		}
		FnSetTextDefault();
	}
	else

	{// EItemRegular, EItemSpecial 이외의 enum 타입에 대한 처리
		//static_assert(false, "Unsupported enum type.");
		static_assert(always_false<TEnum>::value, "Unsupported enum type.");

	{// EItemRegular, EItemSpecial �̿��� enum Ÿ�Կ� ���� ó��
		static_assert(false, "Unsupported enum type.");

	}
}

// ���� �� �÷��̾�� �ǳ� �� ������ ����
template<typename TEnum>
inline void Shop::RegisterItem(Character* player, TEnum _itemType, int _quantity)
{
	static_assert(std::is_enum<TEnum>::value, "itemType must be an enum");

	if constexpr (std::is_same<TEnum, EItemRegular>::value)
	{// EItemRegular�� ���� ó��, �Ϲ� ���� ������
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
	{// EItemSpecial�� ���� ó��, Ư�� ���� ������
		switch (_itemType)
		{
		case EItemSpecial::HolyWater:
			player->addItem(new HolyWater(), _quantity);
			break;
		case EItemSpecial::ChaosOrb:
			player->addItem(new ChaosOrb(), _quantity);
			break;
		case EItemSpecial::END:
			break;
		default:
			break;
		}
	}
	else

	{// EItemRegular, EItemSpecial 이외의 enum 타입에 대한 처리
		//static_assert(false, "Unsupported enum type");
		static_assert(always_false<TEnum>::value, "Unsupported enum type.");

	{// EItemRegular, EItemSpecial �̿��� enum Ÿ�Կ� ���� ó��
		static_assert(false, "Unsupported enum type");

	}
}//END-inline void Shop::RegisterItem
