#include "fls/printer/output_factory.hpp"
#include "fls/printer/output.hpp"

namespace fastlanes {
up<TerminalOutput> OutputFactory::CreateMKD(std::ostream& file_out) {
	auto table_p = std::make_unique<TerminalOutput>();
	// GITHUB Markdown table
	table_p->m_horizontal = "";
	table_p->m_vertical   = "|";
	table_p->m_top_rgt    = " ";
	table_p->m_top_mid    = " ";
	table_p->m_top_lft    = " ";
	table_p->m_bot_rgt    = " ";
	table_p->m_bot_mid    = " ";
	table_p->m_bot_lft    = " ";
	table_p->m_mid_rgt    = " ";
	table_p->m_mid_mid    = " ";
	table_p->m_mid_lft    = " ";
	table_p->m_has_ruler  = true;
	table_p->m_out        = &file_out;

	// csv
	table_p->m_vertical = " ";
	table_p->m_mid_mid  = ",";
	table_p->m_mid_rgt  = ",";
	table_p->m_mid_lft  = ",";

	// table
	//	: m_horizontal("─")
	//, m_vertical("│")
	//, m_top_rgt("┐")
	//, m_top_mid("┬")
	//, m_top_lft("┌")
	//, m_bot_rgt("┘")
	//, m_bot_mid("┴")
	//, m_bot_lft("└")
	//, m_mid_rgt("┤")
	//, m_mid_mid("┼")
	//, m_mid_lft("├")
	//, m_has_ruler(true)
	//, m_out {nullptr} {}

	table_p->Add("FUNC");
	table_p->Add("KEY");
	table_p->Add("VAL");
	table_p->Add("LOCATION");
	table_p->EndOfRow();

	return table_p;
}

up<CsvOutput> OutputFactory::CreateCSV(std::ostream& file_out) {
	auto table_p   = std::make_unique<CsvOutput>();
	table_p->m_out = &file_out;
	table_p->Add("FUNC");
	table_p->Add("KEY");
	table_p->Add("VAL");
	table_p->Add("LOCATION");
	table_p->EndOfRow();
	return table_p;
}

up<TerminalOutput> OutputFactory::CreateTerminal() {
	auto table_p = std::make_unique<TerminalOutput>();

	// table
	table_p->m_horizontal = ("─");
	table_p->m_vertical   = ("│");
	table_p->m_top_rgt    = ("┐");
	table_p->m_top_mid    = ("┬");
	table_p->m_top_lft    = ("┌");
	table_p->m_bot_rgt    = ("┘");
	table_p->m_bot_mid    = ("┴");
	table_p->m_bot_lft    = ("└");
	table_p->m_mid_rgt    = ("┤");
	table_p->m_mid_mid    = ("┼");
	table_p->m_mid_lft    = ("├");
	table_p->m_has_ruler  = true;

	return table_p;
}
} // namespace fastlanes