<?hh // partial

namespace HHPack\Package\Examples;

require_once __DIR__.'/../vendor/hh_autoload.php';

use HHPack\Package;
use HHPack\Package\VendorPackage;

<<__Entrypoint>>
function instantiate_main(): noreturn {
  $package = VendorPackage::fromItems(
    [
      Pair {
        'HHPack\\Package\\Examples\\Classes\\',
        realpath(__DIR__.'/src'),
      },
    ],
  );
  $instances = $package->classes()->map(($class) ==> $class->instantiate());
  $instances->forEach(
    ($instance) ==> {
      var_dump($instance);
    },
  );

  exit(0);
}
