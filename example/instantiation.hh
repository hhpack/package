<?hh // partial

namespace hhpack\package\examples;

require_once __DIR__ . '/../vendor/autoload.php';

use hhpack\package;

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
