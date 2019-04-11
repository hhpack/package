/**
 * This file is part of hhpack\package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Package;

use \ReflectionClass;
use \ReflectionException;

final class VendorPackage implements FromItems<Pair<string, string>> {

  private ImmVector<VendorNamespace> $namespaces;

  public function __construct(Traversable<VendorNamespace> $namespaces) {
    $this->namespaces = ImmVector::fromItems($namespaces);
  }

  public function sources(
    (function(SourceFile): bool) $matcher = any(),
  ): Stream<SourceFile> {
    $results =
      $this->namespaces->map(($namespace) ==> $namespace->sources($matcher));

    return ResourceStream::fromItems($results)
      ->reduce(new ResourceStream(), ($a, $b) ==> $a->concat($b));
  }

  public function classes(
    (function(ClassObject): bool) $matcher = any(),
  ): Stream<ClassObject> {
    $results =
      $this->namespaces->map(($namespace) ==> $namespace->classes($matcher));

    return ResourceStream::fromItems($results)
      ->reduce(new ResourceStream(), ($a, $b) ==> $a->concat($b));
  }

  public static function fromItems(
    Traversable<Pair<string, string>> $items,
  ): this {
    $results = ImmVector::fromItems($items)
      ->map(($item) ==> VendorNamespace::of($item));
    return new static($results);
  }

}
