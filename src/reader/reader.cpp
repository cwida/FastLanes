#include "fls/reader/reader.hpp"
#include "fls/connection.hpp"                     // for Connector (ptr only)
#include "fls/cor/lyt/buf.hpp"                    // for Buf
#include "fls/csv/csv.hpp"                        // for CSV
#include "fls/expression/interpreter.hpp"         // for Interpreter
#include "fls/expression/physical_expression.hpp" // for PhysicalExpr
#include "fls/footer/rowgroup_footer.hpp"         // for Footer, ColumnMeta...
#include "fls/io/file.hpp"                        // for File
#include "fls/io/io.hpp"                          // for IO, io
#include "fls/json/fls_json.hpp"
#include "fls/json/nlohmann/json.hpp" // for json
#include "fls/reader/horizontal_column.hpp"
#include "fls/table/chunk.hpp" // for Chunk
#include <filesystem>          // for operator/, path
#include <memory>              // for make_unique, uniqu...
#include <string>              // for basic_string

namespace fastlanes {
Reader::Reader(const path& dir_path, Connection& fls) {
	// read footer
	{
		auto                 json_string     = File::read(dir_path / FOOTER_FILE_NAME);
		const nlohmann::json j               = nlohmann::json::parse(json_string);
		auto                 rowgroup_footer = j.get<Footer>();
		m_footer                             = make_unique<Footer>(rowgroup_footer);
	}

	// read file
	{
		// allocate buffer
		m_buf = make_unique<Buf>(m_footer->rowgroup_size);         // todo[memory_pool]
		io io = make_unique<File>(dir_path / FASTLANES_FILE_NAME); // todo[IO]
		IO::read(io, *m_buf);
		m_fls_rg = make_unique<FLSRowgroup>(m_buf->Span(), *m_footer);
	}

	// init expression
	{
		m_expressions.reserve(m_footer->size());
		for (const auto& col_mtd : m_footer->column_metadatas) {
			m_expressions.emplace_back(make_unique<PhysicalExpr>());

			Interpreter::State state;
			Interpreter::Decoding::Interpret(col_mtd.encoding_rpn, *m_expressions.back(), state);
		}
	}

	// init chunk
	{ m_chunk = make_unique<Chunk>(m_expressions); }
}

Chunk& Reader::get_chunk(n_t vec_idx) { return *m_chunk; }

void Reader::reset() { m_chunk.reset(); }

void Reader::to_csv(const path& dir_path) {
	for (n_t vec_idx {0}; vec_idx < m_footer->n_vec; vec_idx++) {
		auto& chunk = get_chunk(vec_idx);
		CSV::write(dir_path, chunk);
	};
}

} // namespace fastlanes