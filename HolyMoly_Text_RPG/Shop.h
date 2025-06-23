#pragma once
#include "common.h"
#include "Item.h"
#include "HealthPotion.h"
#include "AttackBoost.h"

class Character;

enum class EMenu;
enum class EYesNo;

enum class EItem
{
	HealthPotion,	// 0
	AttackBoost,	// 1
	END
};

class Shop
{
public:
	Shop();

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
	void DisplayPlayerInventory(Character* player, bool _isSell, bool _isSuccessDeal = false, EItem _item = EItem::END, string _key = "");

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
	void RegisterItem(Character* player, EItem _itemType);

	// 판매 시 아이템 줄이기
	void ReduceItem(Character* player, string _strKey);

	// 입력값 유효성 검사
	string CheckInputValidation(int _min, int _max, Character* player, bool _isPurcahseMode = false);

private:
	// 판매 중인 아이템
	//vector<> availableItems;
	//vector<Item*> availableItems;
	map<EItem, unique_ptr<Item>>availableItems;

	// 최초 진입 여부 확인
	bool mIsFirstEntry;

	// 할인율
	const float mSaleRatio;
};