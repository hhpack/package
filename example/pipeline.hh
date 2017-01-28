<?hh // partial

namespace HHPack\Package\examples;

require_once __DIR__ . '/../vendor/autoload.php';

use HHPack\Package;
use HHPack\Package\Examples\Classes\FileStatOutput;
use HHPack\Package\Examples\Classes\FileStatStream;
use HHPack\Package\Examples\Classes\FileStatTransformer;
use HHPack\Package\VendorPackage;

function pipeline_main() : void
{
    $package = VendorPackage::fromItems([
        Pair { 'HHPack\\Package\\Examples\\Classes\\', realpath(__DIR__ . '/src') }
    ]);

    $package->sources()->pipeTo(new FileStatTransformer())->pipeTo(new FileStatOutput());
}

pipeline_main();
