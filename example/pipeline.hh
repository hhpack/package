<?hh // partial

namespace HHPack\Package\examples;

require_once __DIR__.'/../vendor/hh_autoload.php';

use HHPack\Package;
use HHPack\Package\Examples\Classes\{
  FileStatOutput,
  FileStatStream,
  FileStatTransformer,
};
use HHPack\Package\VendorPackage;

<<__Entrypoint>>
function pipeline_main(): noreturn {
  $package = VendorPackage::fromItems(
    [
      Pair {
        'HHPack\\Package\\Examples\\Classes\\',
        realpath(__DIR__.'/src'),
      },
    ],
  );

  $package->sources()
    ->pipeTo(new FileStatTransformer())
    ->pipeTo(new FileStatOutput());

  exit(0);
}
