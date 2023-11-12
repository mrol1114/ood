#pragma once

#include "IBeverage.h"

class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string& description)
		:m_description(description)
	{}

	std::string GetDescription()const override final
	{
		return m_description;
	}

private:
	std::string m_description;
};

// Êîôå
class CCoffee : public CBeverage
{
public:
	CCoffee(const std::string& description = "Coffee")
		:CBeverage(description)
	{}

	double GetCost() const override
	{
		return 60;
	}
};

// Êàïó÷÷èíî
class CCappuccino : public CCoffee
{
public:
	CCappuccino()
		:CCoffee("Cappuccino")
	{}

	double GetCost() const override
	{
		return 80;
	}
};

class CDoubleCappuccino : public CCoffee
{
public:
	CDoubleCappuccino()
		:CCoffee("Double cappuccino")
	{}

	double GetCost() const override
	{
		return 120;
	}
};

// Ëàòòå
class CLatte : public CCoffee
{
public:
	CLatte()
		:CCoffee("Latte")
	{}

	double GetCost() const override
	{
		return 90;
	}
};

class CDoubleLatte : public CCoffee
{
public:
	CDoubleLatte()
		:CCoffee("Double latte")
	{}

	double GetCost() const override
	{
		return 130;
	}
};

// ×àé
class CTea : public CBeverage
{
public:
	CTea(const std::string& description = "Tea")
		:CBeverage(description)
	{}

	double GetCost() const override
	{
		return 30;
	}
};

class CMilkOolongTea : public CTea
{
public:
	CMilkOolongTea()
		:CTea("Milk oolong tea")
	{}
};

class CBlackTea : public CTea
{
public:
	CBlackTea()
		:CTea("Black tea")
	{}
};

class CEarlGreyTea : public CTea
{
public:
	CEarlGreyTea()
		:CTea("Earl grey tea")
	{}
};

class ÑCheekyFruitTea : public CTea
{
public:
	ÑCheekyFruitTea()
		:CTea("Cheeky fruit tea")
	{}
};

// Ìîëî÷íûé êîêòåéëü
class CSmallMilkshake : public CBeverage
{
public:
	CSmallMilkshake()
		:CBeverage("Small milkshake")
	{}

	double GetCost() const override
	{
		return 50;
	}
};

class CMediumMilkshake : public CBeverage
{
public:
	CMediumMilkshake()
		:CBeverage("Medium milkshake")
	{}

	double GetCost() const override
	{
		return 60;
	}
};

class CBigMilkshake : public CBeverage
{
public:
	CBigMilkshake()
		:CBeverage("Big milkshake")
	{}

	double GetCost() const override
	{
		return 80;
	}
};