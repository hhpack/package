<?hh //strict

/**
 * This file is part of hhpack\package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Package;

use Exception;
use ReflectionClass;
use ReflectionException;

final class ClassObject implements NamedObject {

  public function __construct(private ReflectionClass $class) {}

  /**
   * Get namespace
   */
  public function namespace(): string {
    return $this->class->getNamespaceName();
  }

  /**
   * Get source file name
   */
  public function fileName(): string {
    //see reflection.hhi:51
    return (string) $this->class->getFileName();
  }

  /**
   * Get package directory path
   */
  public function directory(): string {
    return dirname($this->fileName());
  }

  public function name(): string {
    return $this->class->getShortName();
  }

  /**
   * Get class full name
   */
  public function fullName(): string {
    return $this->class->getName();
  }

  /**
   * Get new instance
   */
  public function instantiate<T>(array<mixed> $parameters = []): T {
    try {
      $instance = $this->class->newInstanceArgs($parameters);
    } catch (Exception $exception) {
      throw new InstantiationException($this->fullName());
    }

    return $instance;
  }

  public function implementsInterface(string $interfaceName): bool {
    try {
      $result = $this->class->implementsInterface($interfaceName);
    } catch (ReflectionException $exception) {
      $result = false;
    }

    return $result;
  }

  public function isSubclassOf(string $className): bool {
    return $this->class->isSubclassOf($className);
  }

  public function isAbstract(): bool {
    return $this->class->isAbstract();
  }

  public function isTrait(): bool {
    return $this->class->isTrait();
  }

  public function isInterface(): bool {
    return $this->class->isInterface();
  }

  public function isInstantiable(): bool {
    return $this->class->isInstantiable();
  }

}
