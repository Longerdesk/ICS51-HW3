#include "catch_amalgamated.hpp"
#include "Wordset.hpp"
#include "convert.hpp"
#include <string>
#include <fstream>

namespace{


// NOTE:  these are not intended as exhaustive tests.
// This should get you started testing.


TEST_CASE("InsertTest", "[NotRequiredTable]")
{
	WordSet ws(11);
	ws.insert("sleepy");
	ws.insert("happy");
	ws.insert("dopey");
	ws.insert("sneezy");
	ws.insert("datalink");
	ws.insert("australia");
	ws.insert("guacamole");
	ws.insert("phylum");
	REQUIRE(ws.contains("happy"));
	REQUIRE(ws.getCapacity() == 11);
}

TEST_CASE("Hf1", "[RequiredTable]")
{
	unsigned hv = polynomialHashFunction("dbc", 37, 100000);
	unsigned shouldBe = 4*37*37 + 2*37 + 3;
	REQUIRE(hv == shouldBe);
}


TEST_CASE("Tab1", "[RequiredTable]")
{
	WordSet ws(11);
	ws.insert("dbc");
	REQUIRE(ws.contains("dbc"));
	REQUIRE(ws.getCapacity() == 11);
}


TEST_CASE("Tab2", "[RequiredTable]")
{
	WordSet ws(11);
	ws.insert("sleepy");
	ws.insert("happy");
	ws.insert("dopey");
	ws.insert("sneezy");
	ws.insert("datalink");
	ws.insert("australia");
	ws.insert("guacamole");
	ws.insert("phylum");
	REQUIRE(ws.contains("happy"));
	REQUIRE(ws.contains("dopey"));
	REQUIRE(ws.getCapacity() == 11 );
}


// this test case is not required, in the sense
// that it is not a prerequisite to grading part 1.
// However, I am providing it in hopes that it helps
// you to test your code.
// The functionality is still needed for full credit!
TEST_CASE("ResizeTest", "[SupplementalTable]")
{
	WordSet ws(11);
	ws.insert("sleepy");
	ws.insert("happy");
	ws.insert("dopey");
	ws.insert("sneezy");
	ws.insert("datalink");
	ws.insert("australia");
	ws.insert("guacamole");
	ws.insert("phylum");
	REQUIRE(ws.contains("happy"));
	REQUIRE(ws.contains("dopey"));
	ws.insert("salsa");
	ws.insert("sloth");
	ws.insert("colossus");
	ws.insert("synergize");
	ws.insert("monday");
	ws.insert("tuesday");
	ws.insert("wednesday");
	ws.insert("thursday");
	ws.insert("friday");
	ws.insert("saturday");
	ws.insert("sunday");
	ws.insert("sunday");
	REQUIRE(ws.contains("monday"));
	REQUIRE(ws.contains("sunday"));
	REQUIRE(ws.getCapacity() == 23);
}

TEST_CASE("RemoveTest", "[NonSupplementalTable]")
{
	WordSet ws(11);
	ws.insert("sleepy");
	ws.insert("happy");
	ws.insert("dopey");
	ws.insert("sneezy");
	ws.insert("datalink");
	ws.insert("australia");
	ws.insert("guacamole");
	ws.insert("phylum");
	REQUIRE(ws.contains("happy"));
	REQUIRE(ws.contains("dopey"));
	ws.remove("happy");
	REQUIRE(!ws.contains("happy"));
	ws.insert("salsa");
	ws.insert("sloth");
	ws.insert("colossus");
	ws.insert("synergize");
	ws.insert("monday");
	ws.insert("tuesday");
	ws.insert("wednesday");
	ws.insert("thursday");
	ws.insert("friday");
	ws.insert("saturday");
	ws.insert("sunday");
	ws.insert("sunday");
	ws.insert("colony");
	ws.insert("halloween");
	ws.insert("asult");
	ws.insert("homework");
	ws.insert("own");
	ws.insert("owl");
	REQUIRE(ws.contains("monday"));
	REQUIRE(ws.contains("sunday"));
	REQUIRE(ws.getCapacity() == 23);
}


TEST_CASE("CounttTest", "[NonSupplementalTable]")
{
	WordSet ws(11);
	ws.insert("sleepy");
	ws.insert("happy");
	ws.insert("dopey");
	ws.insert("sneezy");
	ws.insert("datalink");
	ws.insert("australia");
	ws.insert("guacamole");
	ws.insert("phylum");
	ws.insert("salsa");
	ws.insert("sloth");
	ws.insert("colossus");
	ws.insert("synergize");
	ws.insert("monday");
	ws.insert("tuesday");
	ws.insert("wednesday");
	ws.insert("thursday");
	ws.insert("friday");
	ws.insert("saturday");
	ws.insert("sunday");
	ws.insert("colony");
	ws.insert("halloween");
	ws.insert("asult");
	ws.insert("homework");
	ws.insert("own");
	ws.insert("owl");
	REQUIRE(ws.getCount() == 24);
}

}