<?hh // partial

namespace package\examples;

require_once __DIR__ . '/../vendor/autoload.php';

use package\PackageSpecification;

$params = shape(
    'namespace' => 'package\\examples\\classes\\',
    'packageDirectory' => realpath(__DIR__ . '/src')
);
$package = new PackageSpecification($params);

foreach ($package->getSourceFiles() as $source) {
    $instance = $package->resolve($source);
    var_dump($instance);
}
