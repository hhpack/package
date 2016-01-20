<?hh // partial

namespace hhpack\package\examples;

require_once __DIR__ . '/../vendor/autoload.php';

use hhpack\package;

function instantiate_main() : void
{
    $classes = package\package(shape(
        'namespace' => 'hhpack\\package\\examples\\classes\\',
        'packageDirectory' => realpath(__DIR__ . '/src')
    ))->classes()->toImmVector();

    foreach ($classes as $class) {
        $instance = $class->instantiate();
        var_dump($instance);
    }
}

instantiate_main();
