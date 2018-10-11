<?hh //strict

namespace HHPack\Package\Test;

use HHPack\Package as package;
use HHPack\Package\{ClassObject, SourceFile};
use HHPack\Package\Test\Mock\ResourceMock;
use HHPack\Package\Test\Fixtures\{Base, Example1};
use ReflectionClass;
use type Facebook\HackTest\HackTest;
use function Facebook\FBExpect\expect;

final class ShortcutTest extends HackTest {
  public function testStartsWithWhenMatched(): void {
    $item = new ResourceMock('foobar');
    $matcher = package\startsWith('foo');

    expect($matcher($item))->toBeSame(true);
  }

  public function testEndsWithWhenMatched(): void {
    $item = new ResourceMock('foobar');
    $matcher = package\endsWith('bar');

    expect($matcher($item))->toBeTrue();
  }

  public function testImplementsInterfaceWhenUnmatched(): void {
    $item = new ClassObject(new ReflectionClass((string)Example1::class));
    $matcher = package\implementsInterface(Iterator::class);

    expect($matcher($item))->toBeFalse();
  }

  public function testSubclassOfWhenMatched(): void {
    $item = new ClassObject(new ReflectionClass((string)Example1::class));
    $matcher = package\subclassOf(Base::class);

    expect($matcher($item))->toBeTrue();
  }

  public function testSubclassOfWhenUnmatched(): void {
    $item = new ClassObject(new ReflectionClass((string)Example1::class));
    $matcher = package\subclassOf(Iterator::class);

    expect($matcher($item))->toBeFalse();
  }
}
