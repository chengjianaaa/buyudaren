﻿#include "TipWin.h"
#include "GameScene.h"
#include "LoadScene.h"

USING_NS_CC;

bool TipWin::Init(bool GlobalOpen)
{
	auto bg = Sprite::create("images/Scene/GiftScene/bg.png");
	this->addChild(bg);
	auto BtnItem = MenuItemImage::create("images/Scene/GiftScene/btn_got.png","images/Scene/GiftScene/btn_got.png",
		[=](Ref *sender) {
		if(GlobalOpen)
		{
			G_MainGame->m_tipOpen = false;
		}
		this->Get();
	});
	auto BtnClose = MenuItemImage::create("images/Common/btn_close2.png","images/Common/btn_close2.png",[=](Ref *sender){
		if(GlobalOpen)
		{
			G_MainGame->m_tipOpen = false;
		}
		this->CLosePop();
	});

	auto m_menus = Menu::create(BtnItem,BtnClose,NULL);
	this->addChild(m_menus,1);
	m_menus->setPosition(0,0);
	BtnItem->setPosition(10,-150);
	auto Effects = ScaleTo::create(0.3f,1.2f,1.2f);
	auto Effects1=ScaleTo::create(0.3f,1.0f,1.f);
	auto seq = Sequence::create(Effects,Effects1,NULL);
	BtnItem->runAction(RepeatForever::create(seq));
	BtnClose->setPosition(190,85);
	auto GetPng = Sprite::create("images/Scene/GiftScene/word_get.png");
	this->addChild(GetPng,1);
	GetPng->setPosition(-100,0);
	
	auto NoStop = Sprite::create("images/Scene/GiftScene/word_top.png");
	this->addChild(NoStop,1);
	NoStop->setPosition(-10,50);
	AddFlash();
	return true;
}

void TipWin::AddFlash()
{
	auto plashbg = Sprite::create("images/Scene/TipScene/itemGet/bg_light.png");
	this->addChild(plashbg,3);
	plashbg->setPosition(0,0);
	auto rote = RotateBy::create(2.f,360.0f);
	plashbg->runAction(RepeatForever::create(rote));
	LoadGift();
}

void TipWin::LoadGift()
{
	if(m_type == 0)
	{
		auto Coin4 = Sprite::create("images/Scene/ShopScene/money/coin6.png");
		auto Labe = LabelAtlas::create("0","images/Number/gift_coin.png",22,28,'0');
		this->addChild(Coin4,5);
		Coin4->setPosition(0,-25);
		this->addChild(Labe,5);
		Labe->setPosition(-30,-105);
		switch (rand() % 3)
		{
		case 0:
			m_curGold = 500;
			Labe->setString("500");
			break;
		case 1:
			m_curGold = 800;
			Labe->setString("800");
			break;
		case 2:
			m_curGold = 1000;
			Labe->setString("1000");
			break;
		}
	}
	else if(m_type == 3)
	{
		Show12();
	}
	else 
	{
		switch (rand() % 3)
		{
		case 0://6
			{
				auto Prop = Sprite::create("images/Scene/GameScene/prop007.png");
				auto XProp = Sprite::create("images/Number/x_gift.png");
				auto numbp = LabelAtlas::create("3","images/Number/gift_prop.png",20,30,'0');
				this->addChild(XProp,5);
				this->addChild(Prop,5);
				this->addChild(numbp,5);
				Prop->setPosition(5,-15);
				Prop->setScale(0.8f,0.8f);
				numbp->setPosition(20,-100);
				XProp->setPosition(-5,-90);
                auto rmb = Label::createWithSystemFont("仅需6元", "Arial", 20);
                this->addChild(rmb,2);
                rmb->setColor(Color3B(170,99,85));
                rmb->setPosition(Vec2(-100,-40));
			}
			break;
		case 1://10
			{
				auto Coin4 = Sprite::create("images/Scene/ShopScene/money/coin6.png");
				auto Labe = LabelAtlas::create("27000","images/Number/gift_coin.png",22,28,'0');
				this->addChild(Coin4,5);
				Coin4->setPosition(0,-25);
				this->addChild(Labe,5);
				Labe->setPosition(-30,-105);
                auto rmb = Label::createWithSystemFont("仅需10元", "Arial", 20);
                this->addChild(rmb,2);
                rmb->setColor(Color3B(170,99,85));
                rmb->setPosition(Vec2(-100,-40));
			}
			break;
		case 2://12
			Show12();
			break;
		}
	}
}


void TipWin::ShowTip(int sType)
{
	ShowTip(sType,false);
}

void TipWin::ShowTip(int stype, bool IsGlobal)
{
	TipWin *popwin = new TipWin();
	popwin->setPopType(stype);
	if (popwin&&popwin->Init(IsGlobal))
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		popwin->setPosition(Vec2(visibleSize.width * 0.5f,visibleSize.height * 0.5f));
		popwin->setScale(0.5);
		auto action = ScaleTo::create(0.2, 1.3,1.3,1);
		auto raction = ScaleTo::create(0.1, 1,1,1);
		auto q = Sequence::create(action, raction, NULL);
		popwin->runAction(q);
		if(G_MainGame)
		{
			G_MainGame->addChild(popwin,1000);
		}
		else if(LoadScene::m_loadScene)
		{
			LoadScene::m_loadScene->addChild(popwin,1000);
		}
	}

}

void TipWin::CLosePop()
{
	BUBBLE;
	auto action = ScaleTo::create(0.15, 1.3, 1.3, 1);
	auto raction = ScaleTo::create(0.07, 0.5, 0.5, 1);
	CallFunc *call = CallFunc::create(std::bind(&TipWin::CloseAnimation, this));
	auto q = Sequence::create(action, raction, call, NULL);
	this->runAction(q);
}

void TipWin::Get()
{
	//sdk get
	if(m_type == 0)
	{
		Player::getInstance()->AddGold(m_curGold);
	}
	CLosePop();
}

void TipWin::Show12()
{
	auto Coin4 = Sprite::create("images/Scene/ShopScene/money/coin6.png");
	auto Labe = LabelAtlas::create("38000","images/Number/gift_coin.png",22,28,'0');
	auto Give = Sprite::create("images/Scene/GiftScene/give.png");
	auto Prop = Sprite::create("images/Scene/GameScene/prop007.png");
	auto XProp = Sprite::create("images/Number/x_gift.png");
	auto numbp = LabelAtlas::create("2","images/Number/gift_prop.png",20,30,'0');
	this->addChild(numbp,5);
	this->addChild(XProp,5);
	this->addChild(Coin4,5);
	this->addChild(Give,5);
	this->addChild(Prop,5);
	Prop->setPosition(147,-55);
	Prop->setScale(0.5f,0.5f);
	Give->setPosition(80,-45);
	Give->setRotation(25.f);
	Coin4->setPosition(0,-25);
	Coin4->setScale(0.8f,0.8f);
	this->addChild(Labe,5);
	Labe->setPosition(-50,-105);
	numbp->setPosition(150,-120);
	XProp->setPosition(130,-110);
    auto rmb = Label::createWithSystemFont("仅需12元", "Arial", 20);
    this->addChild(rmb,2);
    rmb->setColor(Color3B(170,99,85));
    rmb->setPosition(Vec2(-100,-40));
}
void TipWin::CloseAnimation()
{
	this->removeFromParentAndCleanup(true);
}
