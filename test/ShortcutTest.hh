<?hh //strict

namespace HHPack\Package\Test;

use HHPack\Package as package;
use HHPack\Package\{ClassObject, SourceFile};
use HHPack\Package\Test\Mock\ResourceMock;
use HHPack\Package\Test\Fixtures\{Base, Example1};
use ReflectionClass;
use HackPack\HackUnit\Contract\Assert;

final class ShortcutTest {
  <<Test>>
  public function startsWithWhenMatched(Assert $assert): void {
    $item = new ResourceMock('foobar');
    $matcher = package\startsWith('foo');

    $assert->bool($matcher($item))->is(true);
  }

  <<Test>>
  public function endsWithWhenMatched(Assert $assert): void {
    $item = new ResourceMock('foobar');
    $matcher = package\endsWith('bar');

    $assert->bool($matcher($item))->is(true);
  }

  <<Test>>
  public function implementsInterfaceWhenUnmatched(Assert $assert): void {
    $item = new ClassObject(new ReflectionClass((string) Example1::class));
    $matcher = package\implementsInterface(Iterator::class);

    $assert->bool($matcher($item))->is(false);
  }

  <<Test>>
  public function subclassOfWhenMatched(Assert $assert): void {
    $item = new ClassObject(new ReflectionClass((string) Example1::class));
    $matcher = package\subclassOf(Base::class);

    $assert->bool($matcher($item))->is(true);
  }

  <<Test>>
  public function subclassOfWhenUnmatched(Assert $assert): void {
    $item = new ClassObject(new ReflectionClass((string) Example1::class));
    $matcher = package\subclassOf(Iterator::class);

    $assert->bool($matcher($item))->is(false);
  }
}
