#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <GeographicLib/SphericalHarmonic.hpp>
#include <GeographicLib/MagneticModel.hpp>

using namespace GeographicLib;
int main() {
  typedef GeographicLib::Math::real real;
  try {
    if (true) {
      MagneticModel mag("/scratch/WMM2010NewLinux/WMM2010ISO.COF");
      real lat, lon, h, t, bx, by, bz, bxt, byt, bzt;
      std::cout << std::setprecision(16);
      while (std::cin >> lat >> lon >> h >> t) {
        mag(lat, lon, h, t, bx, by, bz, bxt, byt, bzt);
        std::cout << by << " " << bx << " " << -bz << " "
                  << byt << " " << bxt << " " << -bzt << "\n";
      }
      return 0;
    }
    int type = 2;
    int N;
    std::string name;
    switch (type) {
    case 0:
      N = 360;
      name = "data_EGM96_360.dat";
      break;
    case 1:
      N = 2190;
      name = "data_EGM2008_2190.dat";
      break;
    case 2:
    default:
      N = 5;
      name = "harmtest.dat";
      break;
    }
    int k = ((N + 1) * (N + 2)) / 2;
    std::vector<double> C(k);
    std::vector<double> S(k);
    name = "/scratch/egm2008/harm/" + name;
    {
      std::ifstream f(name.c_str(), std::ios::binary);
      if (!f.good())
        throw GeographicErr("Cannot open coefficient file");
      f.read(reinterpret_cast<char *>(&C[0]), k * sizeof(double));
      f.read(reinterpret_cast<char *>(&S[0]), k * sizeof(double));
    }
    //    for (int i = 0; i < k; ++i)
    //      std::cout << i << " " << C[i] << " " << S[i] << "\n";
    real lat, lon;
    std::cout << std::setprecision(17);
    real a(0.9L), r(1.2L);
    std::vector<real> Z;
    while (std::cin >> lat >> lon) {
      real
        phi = Math::degree<real>() * lat,
        lam = Math::degree<real>() * lon,
        x = r * (abs(lat) == 90 ? 0 : cos(phi)) * cos(lam),
        y = r * (abs(lat) == 90 ? 0 : cos(phi)) * sin(lam),
        z = r * sin(phi);
      real
        d = 1e-7L,
        dx1 = (SphericalHarmonic::Value(N, C, S, Z, Z, 0, x+d, y, z, a) -
               SphericalHarmonic::Value(N, C, S, Z, Z, 0, x-d, y, z, a))/(2*d),
        dy1 = (SphericalHarmonic::Value(N, C, S, Z, Z, 0, x, y+d, z, a) -
               SphericalHarmonic::Value(N, C, S, Z, Z, 0, x, y-d, z, a))/(2*d),
        dz1 = (SphericalHarmonic::Value(N, C, S, Z, Z, 0, x, y, z+d, a) -
               SphericalHarmonic::Value(N, C, S, Z, Z, 0, x, y, z-d, a))/(2*d),
        dx2, dy2, dz2;
      real
        v1 = SphericalHarmonic::TValue<false, SphericalHarmonic::full>
        (N, C, S, Z, Z, 0, x, y, z, a, dx2, dy2, dz2),
        v2 = SphericalHarmonic::TValue<true, SphericalHarmonic::full>
        (N, C, S, Z, Z, 0, x, y, z, a, dx2, dy2, dz2);
      std::cout << v1 << " " << v2 << "\n";
      std::cout << dx1 << " " << dx2 << "\n"
                << dy1 << " " << dy2 << "\n"
                << dz1 << " " << dz2 << "\n";
    }
  }
  catch (const std::exception& e) {
    std::cerr << "Caught exception: " << e.what() << "\n";
    return 1;
  }
  catch (...) {
    std::cerr << "Caught unknown exception\n";
    return 1;
  }
  return 0;
}