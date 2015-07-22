//Link to Boost
 #define BOOST_TEST_DYN_LINK

//Define our Module name (prints at testing)
 #define BOOST_TEST_MODULE "BaseClassModule"

//VERY IMPORTANT - include this last
#include <boost/test/unit_test.hpp>

#include "ZapSharer.hpp"

// ------------- Tests Follow --------------
BOOST_AUTO_TEST_CASE( constructors )
{
  zap::sharer::ZapSharer sharer;
  int i = 2;
  int j = 2;

//Check default constructor
//Use BOOST_CHECK for small equal checks - true or false
  BOOST_CHECK(i == j);
}

//Name your test cases for what they test
BOOST_AUTO_TEST_CASE( assignment )
{
  int i, j = 2;
  i = j;

//Use BOOST_CHECK_EQUAL if you want the values to be 
//printed out if they mismatch
  BOOST_CHECK_EQUAL(i, 2);
}
