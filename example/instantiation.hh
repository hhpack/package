<?hh // partial

namespace package\examples;

require_once __DIR__ . '/../vendor/autoload.php';

use package\Package;

$params = shape(
    'namespace' => 'package\\examples\\classes\\',
    'packageDirectory' => realpath(__DIR__ . '/src')
);
$package = new Package($params);

foreach ($package->getClassFiles() as $class) {
    $instance = $class->instantiate();
    var_dump($instance);
}
