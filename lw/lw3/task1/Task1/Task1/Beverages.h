#pragma once

#include <map>

#include "IBeverage.h"

class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string& description)
		:m_description(description)
	{}
	// override or final
	std::string GetDescription() const override final
	{
		return m_description;
	}

private:
	std::string m_description;
};

// Кофе
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

// Капучино

enum class CappuccinoSizeType
{
	Standard = 0,
	Double,
};

const std::map<CappuccinoSizeType, std::string> CAPPUCINO_SIZE_NAME = {
	{CappuccinoSizeType::Standard, "Standard"},
	{CappuccinoSizeType::Double, "Double"},
};

class CCappuccino : public CCoffee
{
public:
	CCappuccino(CappuccinoSizeType size)
		:CCoffee(CAPPUCINO_SIZE_NAME.at(size) + " cappucino")
		, m_size(size)
	{}

	double GetCost() const override
	{
		return m_size == CappuccinoSizeType::Standard ? 80 : 120;
	}

private:
	CappuccinoSizeType m_size;
};

// Латте

enum class LatteSizeType
{
	Standard = 0,
	Double,
};

const std::map<LatteSizeType, std::string> LATTE_SIZE_NAME = {
	{LatteSizeType::Standard, "Standard"},
	{LatteSizeType::Double, "Double"},
};

class CLatte : public CCoffee
{
public:
	CLatte(LatteSizeType size)
		: CCoffee(LATTE_SIZE_NAME.at(size) + " latte")
		, m_size(size)
	{}

	double GetCost() const override
	{
		return m_size == LatteSizeType::Standard ? 90 : 130;
	}

private:
	LatteSizeType m_size;
};

// Чай

enum class TeaVarietyType {
	OolongTea = 0,
	BlackTea,
	EarlGreyTea,
	CheekyFruitTea,
};

const std::map<TeaVarietyType, std::string> TEA_VARIETY_NAME = {
	{TeaVarietyType::OolongTea, "Oolong tea"},
	{TeaVarietyType::BlackTea, "Black tea"},
	{TeaVarietyType::EarlGreyTea, "Earl grey tea"},
	{TeaVarietyType::CheekyFruitTea, "Cheeky fruit tea"},
};

class CTea : public CBeverage
{
public:
	CTea(TeaVarietyType variety)
		:CBeverage(TEA_VARIETY_NAME.at(variety))
	{}

	double GetCost() const override
	{
		return 30;
	}
};

// Молочный коктейль

enum class MilkshakeSizeType
{
	Small = 0,
	Medium,
	Big,
};

const std::map<MilkshakeSizeType, std::string> MILKSHAKE_SIZE_NAME = {
	{MilkshakeSizeType::Small, "Small"},
	{MilkshakeSizeType::Medium, "Medium"},
	{MilkshakeSizeType::Big, "Big"},
};

class CMilkshake : public CBeverage
{
public:
	CMilkshake(MilkshakeSizeType size)
		:CBeverage(MILKSHAKE_SIZE_NAME.at(size))
		, m_size(size)
	{}

	double GetCost() const override
	{
		switch (m_size)
		{
		case MilkshakeSizeType::Small:
			return 50;
		case MilkshakeSizeType::Medium:
			return 60;
		case MilkshakeSizeType::Big:
			return 80;
		};
	}

private:
	MilkshakeSizeType m_size;
};