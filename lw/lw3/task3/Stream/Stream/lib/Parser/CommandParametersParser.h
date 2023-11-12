#pragma once

#include <string>
#include <map>
#include <set>
#include <vector>
#include <iostream>

enum class ProcessModeType
{
	Assemble = 0,
	Disassemble = 1,
};

enum class OptionType
{
	Decrypt,
	Encrypt,
	Compress,
	Decompress,
};

struct CryptographyOption
{
	OptionType type;
	unsigned int key;
};

struct Params
{
	std::vector<CryptographyOption> options = {};
	ProcessModeType processMode = ProcessModeType::Assemble;
	std::string inFileName = "";
	std::string outFileName = "";
	bool isNeedToCompress = false;
	bool isNeedToDecompress = false;
};

class CommandParametersParser
{
public:
	Params Parse(int argc, char** argv)
	{
		EnsureArgumentsCountIsValid(argc);
		InitOptionsEncounterCount();

		Params params;

		params.outFileName = argv[argc - 1];
		params.inFileName = argv[argc - 2];
		params.processMode = static_cast<ProcessModeType>(std::stoi(argv[argc - 3]));

		unsigned int argumentIndex = 1;
		while (argumentIndex < argc - m_PARAMETERS_COUNT)
		{
			std::string optionName = argv[argumentIndex];
			if (optionName.size() <= m_OPTION_PREFIX.size()
				|| !m_OPTION_NAME_TO_OPTION_TYPE.contains(optionName.substr(m_OPTION_PREFIX.size())))
			{
				throw std::invalid_argument("Invalid option: " + optionName);
			}

			auto optionType = m_OPTION_NAME_TO_OPTION_TYPE.at(optionName.substr(m_OPTION_PREFIX.size()));
			m_optionsEncounterCount.at(optionType)++;

			EnsureOptionAllowedInThisMode(optionType, params.processMode);
			EnsureOptionEncounterLimitNotPassed(optionType);

			if (optionType == OptionType::Compress)
			{
				params.isNeedToCompress = true;
			}
			else if (optionType == OptionType::Decompress)
			{
				params.isNeedToDecompress = true;
			}
			else if (optionType == OptionType::Encrypt
				|| optionType == OptionType::Decrypt)
			{
				CryptographyOption option;
				option.type = optionType;
				option.key = ParseOptionKey(argv[++argumentIndex]);
				params.options.push_back(option);
			}
			argumentIndex++;
		}

		return params;
	}

private:
	void EnsureArgumentsCountIsValid(int argc)
	{
		if (argc < m_PARAMETERS_COUNT)
		{
			throw std::invalid_argument("Needed at least 3 arguments");
		}
	}

	void EnsureOptionAllowedInThisMode(OptionType optionType, ProcessModeType processModeType)
	{
		if (!m_PROCESS_MODE_ALLOWED_OPTIONS.at(processModeType).contains(optionType))
		{
			throw std::invalid_argument("Invalid option for this mode");
		}
	}

	void EnsureOptionEncounterLimitNotPassed(OptionType type)
	{
		if (m_OPTIONS_ENCOUNTER_LIMITS.at(type) != m_UNLIMITED_OPTION_ENCOUNTER_VALUE
			&& m_optionsEncounterCount.at(type) > m_OPTIONS_ENCOUNTER_LIMITS.at(type))
		{
			throw std::invalid_argument("Invalid option for this mode");
		}
	}

	unsigned int ParseOptionKey(std::string keyStr)
	{
		try
		{
			unsigned int key = std::stoi(keyStr);
			return key;
		}
		catch (std::exception& ex)
		{
			throw std::invalid_argument("Invalid option key");
		}
	}

	void InitOptionsEncounterCount()
	{
		for (auto& [type, count] : m_optionsEncounterCount)
		{
			count = 0;
		}
	}

	const std::string m_OPTION_PREFIX = "--";
	const unsigned int m_UNLIMITED_OPTION_ENCOUNTER_VALUE = 0;
	const unsigned int m_PARAMETERS_COUNT = 3;

	const std::map<std::string, OptionType> m_OPTION_NAME_TO_OPTION_TYPE = {
		{"encrypt", OptionType::Encrypt},
		{"decrypt", OptionType::Decrypt},
		{"compress", OptionType::Compress},
		{"decompress", OptionType::Decompress},
	};

	const std::map<ProcessModeType, std::set<OptionType>> m_PROCESS_MODE_ALLOWED_OPTIONS = {
		{ProcessModeType::Assemble, {OptionType::Encrypt, OptionType::Compress}},
		{ProcessModeType::Disassemble, {OptionType::Decrypt, OptionType::Decompress}},
	};

	const std::map<OptionType, unsigned int> m_OPTIONS_ENCOUNTER_LIMITS = {
		{OptionType::Encrypt, m_UNLIMITED_OPTION_ENCOUNTER_VALUE},
		{OptionType::Decrypt, m_UNLIMITED_OPTION_ENCOUNTER_VALUE},
		{OptionType::Compress, 1},
		{OptionType::Decompress, 1},
	};

	std::map<OptionType, unsigned int> m_optionsEncounterCount = {
		{OptionType::Encrypt, 0},
		{OptionType::Decrypt, 0},
		{OptionType::Compress, 0},
		{OptionType::Decompress, 0},
	};
};