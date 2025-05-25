#include "fls/printer/output.hpp"
#include <fls/std/string.hpp>
#include <fls/std/vector.hpp>
#include <iomanip>

namespace fastlanes {
TerminalOutput::TerminalOutput() = default;

void TerminalOutput::SetAlignment(unsigned int i, TerminalOutput::Align alignment) {
	m_alignment[i] = alignment;
}

TerminalOutput::Align TerminalOutput::Alignment(unsigned int i) const {
	return m_alignment[i];
}

void TerminalOutput::EndOfRow() {
	m_rows.push_back(m_current);
	m_current.assign(0, "");
}

template <typename ITERATOR>
void TerminalOutput::AddRow(ITERATOR begin, ITERATOR end) {
	for (auto i = begin; i != end; ++i) {
		Add(*i);
	}
	EndOfRow();
}

template void TerminalOutput::AddRow<vector<string>::iterator>(vector<string>::iterator begin,
                                                               vector<string>::iterator end);

void TerminalOutput::Setup() const {
	determine_widths();
	setup_alignment();
}

const std::vector<TerminalOutput::row_t>& TerminalOutput::Rows() const {
	return m_rows;
}

std::string TerminalOutput::Ruler(POS pos) const {

	std::string result;
	size_t      i {0};
	std::string lft, mid, rgt;
	switch (pos) {
	case POS::TOP:
		rgt = m_top_rgt;
		mid = m_top_mid;
		lft = m_top_lft;
		break;
	case POS::MID:
		rgt = m_mid_rgt;
		mid = m_mid_mid;
		lft = m_mid_lft;
		break;
	case POS::BOT:
		rgt = m_bot_rgt;
		mid = m_bot_mid;
		lft = m_bot_lft;
		break;
	}

	result += lft;
	for (; i < m_width.size() - 1; ++i) {
		result += repeat(m_width[i], m_horizontal);
		result += mid;
	}

	result += repeat(m_width[i], m_horizontal);
	result += rgt;

	return result;
}

unsigned TerminalOutput::Width(unsigned int i) const {
	return m_width[i];
}

unsigned TerminalOutput::CorrectDistance(const std::string& string_to_correct) const {
	return static_cast<unsigned>(string_to_correct.size() - glyph_length(string_to_correct));
}

bool TerminalOutput::HasRuler() const {
	return m_has_ruler;
}

std::string TerminalOutput::repeat(unsigned int times, const std::string& c) {
	std::string result;
	for (; times > 0; --times) {
		result += c;
	}

	return result;
}

unsigned TerminalOutput::glyph_length(const std::string& s) const {
	auto        byte_length  = s.length();
	int         u            = 0;
	const char* c_str        = s.c_str();
	unsigned    glyph_length = 0;
	while (u < byte_length) {
		u += std::mblen(&c_str[u], byte_length - static_cast<size_t>(u));
		glyph_length += 1;
	}
	return glyph_length;
}

unsigned TerminalOutput::columns() const {
	if (m_rows.empty()) {
		return 0;
	}

	return static_cast<unsigned>(m_rows[0].size());
}

void TerminalOutput::determine_widths() const {
	m_width.assign(columns(), 0);
	m_utf8width.assign(columns(), 0);
	for (const auto& row : m_rows) {
		for (unsigned i = 0; i < row.size(); ++i) {
			m_width[i] = m_width[i] > glyph_length(row[i]) ? m_width[i] : glyph_length(row[i]);
		}
	}
}

void TerminalOutput::setup_alignment() const {
	for (unsigned i = 0; i < columns(); ++i) {
		if (m_alignment.find(i) == m_alignment.end()) {
			m_alignment[i] = Align::LEFT;
		}
	}
}

std::string TerminalOutput::Vertical() const {
	return m_vertical;
}

std::string TerminalOutput::Horizontal() const {
	return m_horizontal;
}

void TerminalOutput::Add(const std::string& content) {
	//
	m_current.push_back(content);
}

template <typename CONTAINER>
void TerminalOutput::AddRow(const CONTAINER& container) {
	for (const auto& i : container) {
		Add(i);
	}
	EndOfRow();
}

template void TerminalOutput::AddRow<vector<string>>(const vector<string>& container);
template void TerminalOutput::AddRow<vector<char const*>>(const vector<char const*>& container);

TerminalOutput::~TerminalOutput() {
	if (m_out) {
		*m_out << *this;
		m_out->flush();
	}
}

void TerminalOutput::Print(std::ostream& os) const {
	os << *this;
}

std::ostream& operator<<(std::ostream& stream, TerminalOutput const& table) {
	table.Setup();
	auto final_iter = table.Rows().end() - 1;

	if (table.HasRuler()) {
		stream << table.Ruler(TerminalOutput::POS::TOP) << "\n";
	}

	// HEADER
	{
		stream << table.Vertical();
		stream << table.m_header;
		stream << "\n";
		if (table.HasRuler()) {
			stream << table.Ruler(TerminalOutput::POS::MID) << "\n";
		}
	}

	// ROWS
	for (auto row_iterator = table.Rows().begin(); row_iterator != table.Rows().end(); ++row_iterator) {
		TerminalOutput::row_t const& row = *row_iterator;
		stream << table.Vertical();
		for (unsigned i = 0; i < row.size(); ++i) {
			auto alignment = table.Alignment(i) == TerminalOutput::Align::LEFT ? std::left : std::right;
			// std::setw( width ) works as follows: a string which goes in the stream with byte length (!) l is filled
			// with n spaces so that l+n=width. For a utf8 encoded string the glyph length g might be smaller than l. We
			// need n spaces so that g+n=width which is equivalent to g+n+l-l=width ==> l+n = width+l-g l-g (that means
			// glyph length minus byte length) has to be added to the width argument. l-g is computed by
			// correctDistance.
			stream << std::setw(static_cast<int>(table.Width(i) + table.CorrectDistance(row[i]))) << alignment
			       << row[i];
			stream << table.Vertical();
		}
		stream << "\n";
		if (row_iterator == final_iter) {
			stream << table.Ruler(TerminalOutput::POS::BOT) << "\n";
			continue;
		}
		if (table.HasRuler()) {
			stream << table.Ruler(TerminalOutput::POS::MID) << "\n";
		}
	}

	return stream;
}

void CsvOutput::Add(const std::string& content) {
	ss << content;
	ss << ",";
}

CsvOutput::~CsvOutput() {
	if (m_out) {
		*m_out << ss.str();
	}
}

void CsvOutput::EndOfRow() {
	ss << "\n";
}
} // namespace fastlanes