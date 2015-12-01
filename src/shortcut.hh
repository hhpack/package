<?hh //strict

/**
 * This file is part of hhpack\package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhpack\package\matcher
{

    use hhpack\package\ClassTypeMatcher;
    use hhpack\package\ClassNameMatcher;

    function implementsInterface(string $interfaceName) : ClassTypeMatcher
    {
        return ClassTypeMatcher::implementsInterface($interfaceName);
    }

    function subclassOf(string $className) : ClassTypeMatcher
    {
        return ClassTypeMatcher::subclassOf($className);
    }

    function classes() : ClassTypeMatcher
    {
        return ClassTypeMatcher::classType();
    }

    function abstractClasses() : ClassTypeMatcher
    {
        return ClassTypeMatcher::abstractClassType();
    }

    function traits() : ClassTypeMatcher
    {
        return ClassTypeMatcher::traitType();
    }

    function interfaces() : ClassTypeMatcher
    {
        return ClassTypeMatcher::interfaceType();
    }

    function startsWith(string $keyword) : ClassNameMatcher
    {
        return ClassNameMatcher::startsWith($keyword);
    }

    function endsWith(string $keyword) : ClassNameMatcher
    {
        return ClassNameMatcher::endsWith($keyword);
    }

}
