#include "soundex.h"
#include <unordered_map>


namespace
{
  constexpr size_t kMAX_CODE_LENGTH{ 4 };
  const std::string kNOT_A_DIGIT{ "*" };
  const std::unordered_map< char, std::string > kENCODINGS{
    { 'b', "1" }, { 'f', "1" }, { 'p', "1" }, { 'v', "1" },
    { 'c', "2" }, { 'g', "2" }, { 'j', "2" }, { 'k', "2" }, { 'q', "2" }, { 's', "2" }, { 'x', "2" }, { 'z', "2" },
    { 'd', "3" }, { 't', "3" },
    { 'l', "4" },
    { 'm', "5" }, { 'n', "5" },
    { 'r', "6" }
  };

  void encodeHead( std::string& encoding, const std::string& word )
  {
    encoding += Soundex::encodedDigit( word.front() );
  }

  std::string lastDigit( const std::string& encoding )
  {
    return encoding.empty() ? kNOT_A_DIGIT : &encoding.back();
  }

  char lower( const char letter )
  {
    return static_cast< char >( std::tolower( static_cast< unsigned char >( letter ) ) );
  }

  bool isVowel( const char last_letter )
  {
    return std::string( "aeiouy" ).find( lower( last_letter ) ) != std::string::npos;
  }

  void encodeLetter( std::string& encoding, const char letter, const char lastLetter )
  {
    if(const auto digit = Soundex::encodedDigit( letter );
      digit != kNOT_A_DIGIT &&
      ( digit != lastDigit( encoding ) || isVowel( lastLetter ) ))
    {
      encoding += digit;
    }
  }

  bool isComplete( const std::string& encoding )
  {
    return encoding.length() == kMAX_CODE_LENGTH;
  }

  void encodeTail( std::string& encoding, const std::string& word )
  {
    for(auto idx = 1U; idx < word.length(); ++idx)
    {
      if(isComplete( encoding ))
      {
        break;
      }
      encodeLetter( encoding, word[ idx ], word[ idx - 1 ] );
    }
  }

  std::string encodedDigits( const std::string& word )
  {
    std::string encoding;
    encodeHead( encoding, word );
    encodeTail( encoding, word );
    return encoding;
  }

  std::string tail( const std::string& word )
  {
    return word.substr( 1 );
  }

  std::string head( const std::string& word )
  {
    return word.substr( 0, 1 );
  }

  std::string upperFront( const std::string& string )
  {
    return std::string( 1, static_cast< char >( std::toupper( string.front() ) ) );
  }

  std::string zeroPad( const std::string& word )
  {
    const auto zerosNeeded = kMAX_CODE_LENGTH - word.length();
    return word + std::string( zerosNeeded, '0' );
  }
}

std::string Soundex::encode( const std::string& word )
{
  return zeroPad( upperFront( head( word ) ) + tail( encodedDigits( word ) ) );
}

std::string Soundex::encodedDigit( const char letter )
{
  const auto it = kENCODINGS.find( lower( letter ) );
  return it == kENCODINGS.end() ? kNOT_A_DIGIT : it->second;
}
