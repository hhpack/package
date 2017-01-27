<?hh // partial

namespace HHPack\Package\Examples;

require_once __DIR__ . '/../vendor/autoload.php';

use HHPack\Package as package;
use HHPack\Package\VendorPackage;

function selector_main() : void
{
    $package = VendorPackage::fromItems([
        Pair { 'hhpack\\package\\examples\\classes\\', realpath(__DIR__ . '/src') }
    ]);

    $package->classes(package\startsWith('Exa'))
        ->forEach(($class) ==> {
            var_dump($class->name());
        });
}
selector_main();
