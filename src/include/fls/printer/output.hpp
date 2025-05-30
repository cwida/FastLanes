#ifndef FLS_PRINTER_OUTPUT_HPP
#define FLS_PRINTER_OUTPUT_HPP

#include "fls/std/string.hpp"
#include "fls/std/vector.hpp"
#include <map>     // for map
#include <sstream> //

namespace fastlanes {
class CsvOutput {
public:
	~CsvOutput();

public:
	void Add(string const& content); //
	void EndOfRow();                 //
public:
	std::stringstream ss;    //
	std::ostream*     m_out; //
};

class TerminalOutput {
public:
	using row_t = vector<string>;               //
	enum class Align : uint8_t { LEFT, RIGHT }; //
	enum class POS : uint8_t { TOP, MID, BOT }; //
	TerminalOutput();                           //
	~TerminalOutput();                          //
public:
	///!
	template <typename ITERATOR>
	void AddRow(ITERATOR begin, ITERATOR end);
	///!
	template <typename CONTAINER>
	void AddRow(CONTAINER const& container);
	///!
	friend std::ostream& operator<<(std::ostream& stream, TerminalOutput const& table);

public:
	void Print(std::ostream& os) const;
	///!
	void                 SetAlignment(unsigned i, Align alignment);              //
	Align                Alignment(unsigned i) const;                            //
	string               Vertical() const;                                       //
	string               Horizontal() const;                                     //
	void                 Add(string const& content);                             //
	void                 EndOfRow();                                             //
	vector<row_t> const& Rows() const;                                           //
	void                 Setup() const;                                          //
	string               Ruler(POS pos) const;                                   //
	unsigned             Width(unsigned i) const;                                //
	bool                 HasRuler() const;                                       //
	unsigned             CorrectDistance(const string& string_to_correct) const; //

private:
	static string repeat(unsigned times, const string& c); //
	unsigned      columns() const;                         //
	unsigned      glyph_length(const string& s) const;     //
	void          determine_widths() const;                //
	void          setup_alignment() const;                 //
	void          add_row();

public:
	string        m_header;                        //
	std::string   m_horizontal;                    //
	string        m_vertical;                      //
	string        m_top_rgt;                       //
	string        m_top_mid;                       //
	string        m_top_lft;                       //
	string        m_bot_rgt;                       //
	string        m_bot_mid;                       //
	string        m_bot_lft;                       //
	string        m_mid_rgt;                       //
	string        m_mid_mid;                       //
	string        m_mid_lft;                       //
	bool          m_has_ruler {};                  //
	row_t         m_current;                       //
	vector<row_t> m_rows;                          //
	vector<unsigned> mutable m_width;              //
	vector<unsigned> mutable m_utf8width;          //
	std::map<unsigned, Align> mutable m_alignment; //
	std::ostream* m_out {};                        //
};

} // namespace fastlanes
#endif // FLS_PRINTER_OUTPUT_HPP
