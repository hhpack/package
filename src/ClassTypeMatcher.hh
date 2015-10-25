<?hh //strict

/**
 * This file is part of hhpack\package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhpack\package;

final class ClassTypeMatcher implements Matcher<ClassObject>
{

    public function __construct(
        private (function(ClassObject):bool) $matcher
    )
    {
    }

    public function matches(ClassObject $item) : bool
    {
        $matcher = $this->matcher;
        return $matcher($item);
    }

    public static function implementsInterface(string $interface) : this
    {
        return new ClassTypeMatcher(
            (ClassObject $class) ==> $class->implementsInterface($interface)
        );
    }

    public static function subclassOf(string $className) : this
    {
        return new ClassTypeMatcher(
            (ClassObject $class) ==> $class->isSubclassOf($className)
        );
    }

    public static function classType() : this
    {
        return new ClassTypeMatcher((ClassObject $class) ==> {
            return ($class->isTrait() || $class->isInterface()) === false;
        });
    }

    public static function abstractClassType() : this
    {
        return new ClassTypeMatcher((ClassObject $class) ==> $class->isAbstract());
    }

    public static function traitType() : this
    {
        return new ClassTypeMatcher((ClassObject $class) ==> $class->isTrait());
    }

    public static function interfaceType() : this
    {
        return new ClassTypeMatcher((ClassObject $class) ==> $class->isInterface());
    }

}
