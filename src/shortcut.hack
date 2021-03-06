/**
 * This file is part of hhpack\package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Package;

function any<T>(): (function(T): bool) {
  return ($object) ==> true;
}

function startsWith<T as NamedObject>(string $keyword): (function(T): bool) {
  return ($object) ==>
    \preg_match('/^'.\preg_quote($keyword, '/').'/', $object->name()) === 1;
}

function endsWith<T as NamedObject>(string $keyword): (function(T): bool) {
  return ($object) ==>
    \preg_match('/'.\preg_quote($keyword, '/').'$/', $object->name()) === 1;
}

function implementsInterface<Tu>(
  classname<Tu> $interfaceName,
): (function(ClassObject): bool) {
  return ($object) ==> $object->implementsInterface($interfaceName);
}

function subclassOf<Tu>(
  classname<Tu> $className,
): (function(ClassObject): bool) {
  return ($object) ==> $object->isSubclassOf($className);
}

function classes(): (function(ClassObject): bool) {
  return ($object) ==> ($object->isTrait() || $object->isInterface()) === false;
}

function abstractClasses(): (function(ClassObject): bool) {
  return ($object) ==> $object->isAbstract();
}

function traits(): (function(ClassObject): bool) {
  return ($object) ==> $object->isTrait();
}

function interfaces(): (function(ClassObject): bool) {
  return ($object) ==> $object->isInterface();
}

function instantiable(): (function(ClassObject): bool) {
  return ($object) ==> $object->isInstantiable();
}
function instantiator<Tu>(
  array<mixed> $parameters = [],
): (function(ClassObject): Tu) {
  return ($object) ==> $object->instantiate($parameters);
}
