<?hh //strict

namespace HHPack\Package\Test;

use ReflectionClass;
use HHPack\Package\ClassObject;
use HHPack\Package\Test\Fixtures\Base;
use HHPack\Package\Test\Fixtures\Example1;
use HackPack\HackUnit\Contract\Assert;

final class ClassObjectTest
{
    <<Test>>
    public function className(Assert $assert): void
    {
        $classFile = new ClassObject(new ReflectionClass((string) Example1::class));
        $assert->string($classFile->fullName())->is((string) Example1::class);
        $assert->string($classFile->name())->is('Example1');
    }

    <<Test>>
    public function isSubclassOfWhenSubclass(Assert $assert): void
    {
        $classFile = new ClassObject(new ReflectionClass((string) Example1::class));
        $assert->bool($classFile->isSubclassOf(Base::class))->is(true);
    }

    <<Test>>
    public function instantiateWhenSpecifyTheParameters(Assert $assert): void
    {
        $classFile = new ClassObject(new ReflectionClass((string) Example1::class));
        $instance = $classFile->instantiate([ 'foo' ]);

        $assert->mixed($instance)->isTypeOf((string) Example1::class);
        $assert->string($instance->getName())->is('foo');
    }

    <<Test>>
    public function instantiateWhenNotSpecifyTheParameters(Assert $assert): void
    {
        $classFile = new ClassObject(new ReflectionClass((string) Example1::class));
        $instance = $classFile->instantiate();

        $assert->mixed($instance)->isTypeOf((string) Example1::class);
    }
}
