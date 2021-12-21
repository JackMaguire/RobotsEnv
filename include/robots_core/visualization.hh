#pragma once

#include <string>
#include <sstream>
#include <vector>

#include <robots_core/board.hh>
#include <robots_core/asserts.hh>

namespace robots_core {

//https://godbolt.org/z/dhPTbPon6
//https://stackoverflow.com/questions/5878775/how-to-find-and-replace-string/5878802
//TODO replace
void
replaceFirstOccurrence(
  std::string & s,
  std::string const & toReplace,
  std::string const & replaceWith
) {
  std::size_t pos = s.find( toReplace );
  s.replace( pos, toReplace.length(), replaceWith );
}

/*void
format(
  std::string & base,
  std::vector< std::string > const & tokens
){
  for( std::string const & s : tokens ){
    replaceFirstOccurrence( base, "%", s );
  }
}*/

template< typename Ostream >
void
to_svg( 
  Board const &,
  Ostream & out
) {
  constexpr int PixPerCell = 10;
  constexpr int PicWidth = Board::WIDTH * PixPerCell;
  constexpr int PicHeight = Board::HEIGHT * PixPerCell;

  //std::string header = R"(<svg width="%" height="%")";
  //  format( 

  std::string header = R"(<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE svg PUBLIC "-//W3C//DTD SVG 1.1//EN" "http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd">
<svg xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" width="100%" height="100%" viewBox="0 0 %%PicWidth%% %%PicHeight%%">
<a xlink:href="http://www.w3.org/Graphics/SVG/" target="_parent"
     xlink:title="W3C SVG Working Group home page">

<rect id="c1" fill="#dcdcdc" width="%%PicWidth%%" height="%%PicHeight%%"/>)"; //";

  replaceFirstOccurrence( header, "%%PicWidth%%", std::to_string( PicWidth ) );
  replaceFirstOccurrence( header, "%%PicWidth%%", std::to_string( PicWidth ) );
  replaceFirstOccurrence( header, "%%PicHeight%%", std::to_string( PicHeight ) );
  replaceFirstOccurrence( header, "%%PicHeight%%", std::to_string( PicHeight ) );

  // Header
  out << header << '\n';

  // Background
  //std::string const c1 = "dcdcdc";
  //std::string const c2 = "c8c8c8";
  bool use_c1 = false;
  for( sm_int i = 0; i < Board::WIDTH; ++i ){
    for( sm_int j = 0; j < Board::HEIGHT; ++j ){
      use_c1 = !use_c1;
      /*
      std::string const & c = ( use_c1 ? c1 : c2 );
      out << "<rect fill=\"" << c << "\" "
	"stroke=\"#000\" stroke-width=\"0\" "
	"x=\"" << i*PixPerCell << "\" "
	"y=\"" << j*PixPerCell << "\" "
	"width=\"" << PixPerCell << "\" "
	"height=\"" << PixPerCell << "\"/>";
	*/
      if( not use_c1 ){
	out << "<rect fill=\"c8c8c8\" width=\"" << PixPerCell << "\" height=\"" << PixPerCell << "\" "
	  "x=\"" << i*PixPerCell << "\" y=\"" << j*PixPerCell << "\" />";
      }
    }
    use_c1 = !use_c1;
  }

  // Footer
  out << "</a>\n</svg>\n";
}

std::string
to_svg_string( Board const & board ) {
  std::stringstream ss;
  to_svg( board, ss );
  return ss.str();
}

} // namespace robots_core
