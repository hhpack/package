<?hh // partial

namespace HHPack\Package\Examples;

require_once __DIR__.'/../vendor/hh_autoload.php';

use HHPack\Package as package;
use HHPack\Package\VendorPackage;

<<__Entrypoint>>
function selector_main(): noreturn {
  $package = VendorPackage::fromItems(
    [
      Pair {
        'HHPack\\Package\\Examples\\Classes\\',
        realpath(__DIR__.'/src'),
      },
    ],
  );

  $package->classes(package\startsWith('Exa'))
    ->forEach(
      ($class) ==> {
        var_dump($class->name());
      },
    );

  exit(0);
}
