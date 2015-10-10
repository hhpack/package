<?hh // partial

namespace package\examples;

require_once __DIR__ . '/../vendor/autoload.php';

use package\Package;

$classes = Package::fromOptions(shape(
    'namespace' => 'package\\examples\\classes\\',
    'packageDirectory' => realpath(__DIR__ . '/src')
))->classes()->toImmVector();

foreach ($classes as $class) {
    $instance = $class->instantiate();
    var_dump($instance);
}
