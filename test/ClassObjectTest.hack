namespace HHPack\Package\Test;

use ReflectionClass;
use HHPack\Package\ClassObject;
use HHPack\Package\Test\Fixtures\{Base, Example1};
use type Facebook\HackTest\HackTest;
use function Facebook\FBExpect\expect;

final class ClassObjectTest extends HackTest {
  public function testClassName(): void {
    $classFile = new ClassObject(new ReflectionClass((string)Example1::class));

    expect($classFile->fullName())->toBeSame((string)Example1::class);
    expect($classFile->name())->toBeSame('Example1');
  }

  public function testIsSubclassOfWhenSubclass(): void {
    $classFile = new ClassObject(new ReflectionClass((string)Example1::class));
    expect($classFile->isSubclassOf(Base::class))->toBeTrue();
  }

  public function testInstantiateWhenSpecifyTheParameters(): void {
    $classFile = new ClassObject(new ReflectionClass((string)Example1::class));
    $instance = $classFile->instantiate(['foo']);

    expect($instance)->toBeInstanceOf(Example1::class);
    expect($instance->getName())->toBeSame('foo');
  }

  public function testInstantiateWhenNotSpecifyTheParameters(): void {
    $classFile = new ClassObject(new ReflectionClass((string)Example1::class));
    $instance = $classFile->instantiate();

    expect($instance)->toBeInstanceOf(Example1::class);
  }
}
