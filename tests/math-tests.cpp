
#include <common.h>
#include <slsmath.h>
#include <catch.hpp>
#include<limits>

constexpr auto epsilon = std::numeric_limits<float>::epsilon();


TEST_CASE("nearf functions")
{
  volatile auto one_tenth = 0.1f;
  volatile auto two_tenths = 0.2f;
  auto sum = one_tenth + two_tenths;
  REQUIRE(sls_nearf(sum, 0.3f, epsilon));
  REQUIRE(!sls_nearf(sum, 0.4, epsilon));
  REQUIRE(sls_nearf(1, 2, 100));
}



TEST_CASE("dot product test", "[vector]")
{
  slsVec2 v0, v1;
  slsVec3 v3, v4;
  float fresult, fexpected;
  SECTION("slsVec2") {
    // test dot product
    v0 = sls_vec2_make(-62.47096805f, -5.87299575f);
    v1 = sls_vec2_make(-217.38856733f, 14.50296503f);
    fexpected = 13495.298f;
    fresult = sls_vec2_dot(&v0, &v1);
    REQUIRE(sls_nearf(fexpected, fresult, epsilon));
  }
  SECTION("slsVec3") {
    v3 = sls_vec3_make(24.814496f, -7.05247768f, -223.76167351f);
    v4 = sls_vec3_make(-236.09291143f, -141.34171468f, 73.15285408f);
    fexpected = -21230.522f;
    fresult = sls_vec3_dot(&v3, &v4);

    REQUIRE(sls_nearf(fexpected, fresult, epsilon));
  }
}
