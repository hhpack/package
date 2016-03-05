<?hh // partial

namespace hhpack\package\examples;

require_once __DIR__ . '/../vendor/autoload.php';

use hhpack\package;
use hhpack\package\examples\classes\FileStatOutput;
use hhpack\package\examples\classes\FileStatStream;
use hhpack\package\examples\classes\FileStatTransformer;
use hhpack\package\VendorPackage;

function pipeline_main() : void
{
    $package = VendorPackage::fromItems([
        Pair { 'hhpack\\package\\examples\\classes\\', realpath(__DIR__ . '/src') }
    ]);

    $package->sources()->pipeTo(new FileStatTransformer())->pipeTo(new FileStatOutput());
}

pipeline_main();
