<?hh // partial

namespace HHPack\Package\Examples;

require_once __DIR__ . '/../vendor/autoload.php';

use HHPack\Package;
use HHPack\Package\VendorPackage;

function instantiate_main() : void
{
    $package = VendorPackage::fromItems([
        Pair { 'hhpack\\package\\examples\\classes\\', realpath(__DIR__ . '/src') }
    ]);
    $instances = $package->classes()->map(($class) ==> $class->instantiate());
    $instances->forEach(($instance) ==> {
        var_dump($instance);
    });
}

instantiate_main();
