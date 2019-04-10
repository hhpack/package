/**
 * This file is part of hhpack\package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Package;

use LazyIterable;

final class ResourceIterator<T> implements Iterable<T>, FromItems<T> {

  use LazyIterable<T>;

  private Traversable<T> $elements;

  public function __construct(Traversable<T> $elements = []) {
    $this->elements = $elements;
  }

  public function getIterator(): Iterator<T> {
    foreach ($this->elements as $element) {
      yield $element;
    }
  }

  public static function fromItems(Traversable<T> $items): this {
    return new static($items);
  }

}
