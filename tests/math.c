
#include <common.h>
#include <slsmath.h>

#ifdef NDEBUG
#undef NDEBUG
#endif


void dot_tests()
{
  slsVec2 v0, v1;
  slsVec3 v3, v4;
  float fresult, fexpected;

  // test dot product
  v0 = sls_vec2_make(-62.47096805f, -5.87299575f);
  v1 = sls_vec2_make(-217.38856733f, 14.50296503f);
  fexpected = 13495.2983928676f;
  fresult = sls_vec2_dot(&v0, &v1);
  assert(sls_nearf(fexpected, fresult));


  v3 = sls_vec3_make(24.814496f, -7.05247768f, -223.76167351f);
  v4 = sls_vec3_make(-236.09291143f, -141.34171468f, 73.15285408f);
  fexpected = -21230.522f;
  fresult = sls_vec3_dot(&v3, &v4);

  assert(sls_nearf(fexpected, fresult));

}

void run_math_tests()
{
  dot_tests();
}
