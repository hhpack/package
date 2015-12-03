<?hh //strict

/**
 * This file is part of hhpack\package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhpack\package\selector;

use hhpack\package\ClassTypeMatcher;
use hhpack\package\NameMatcher;
use hhpack\package\NamedObject;

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

function startsWith(string $keyword) : NameMatcher<NamedObject>
{
    return NameMatcher::startsWith($keyword);
}

function endsWith(string $keyword) : NameMatcher<NamedObject>
{
    return NameMatcher::endsWith($keyword);
}
