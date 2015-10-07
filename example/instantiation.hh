<?hh // partial

namespace package\examples;

require_once __DIR__ . '/../vendor/autoload.php';

use package\Package;

$package = Package::fromOptions(shape(
    'namespace' => 'package\\examples\\classes\\',
    'packageDirectory' => realpath(__DIR__ . '/src')
));

foreach ($package->getClassFiles() as $class) {
    $instance = $class->instantiate();
    var_dump($instance);
}
