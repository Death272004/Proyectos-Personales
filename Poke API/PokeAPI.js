document.addEventListener('DOMContentLoaded', () => {
    const buscarBtn = document.querySelector('.btn-buscar');
    const buscarBtnAlt = document.querySelector('.btn-buscard');
    const inputText = document.querySelector('.input-text');
    const tipoBusqueda = document.querySelector('.select-busqueda');

    function manejarClickBuscar() {
        if (!inputText) return console.error('No se encontró el input `.input-text`.');
        const busqueda = (inputText.value || '').toLowerCase();
        const tipo = tipoBusqueda ? tipoBusqueda.value : null;
        if (!busqueda) {
            alert('Por favor, ingresa un valor para buscar.');
            return;
        }
        if (tipo === 'habilidad') {
            buscarPorHabilidad(busqueda);
        } else {
            buscarPokemon(busqueda);
        }
    }
    
    function resetearVista() {
        if (inputText) inputText.value = '';
        const contenedor = document.getElementById('resultado-container');
        if (contenedor) contenedor.style.display = 'none';
        const info = document.querySelector('.pokemon-info');
        if (info) info.innerHTML = '';
    }
    if (buscarBtn) buscarBtn.addEventListener('click', manejarClickBuscar);
    if (buscarBtnAlt) buscarBtnAlt.addEventListener('click', resetearVista);
    const favoritosBtn = document.querySelector('.btn-favoritos');
    if (favoritosBtn) favoritosBtn.addEventListener('click', mostrarFavoritos);
    const historicoBtn = document.querySelector('.btn-historico');
    if (historicoBtn) historicoBtn.addEventListener('click', mostrarHistorial);
    const vsBtn = document.querySelector('.btn-vs');
    if (vsBtn) vsBtn.addEventListener('click', mostrarVistaVS);
    console.log('Inicializado buscador:', { buscarBtn, buscarBtnAlt, inputText, tipoBusqueda });
});


// Función única para buscar Pokémon por nombre o ID
function buscarPokemon(query) {
    const queryNormalizado = typeof query === 'string' ? query.toLowerCase() : query;
    const historial = JSON.parse(localStorage.getItem('pokemonHistorial') || '[]');
    const isLocal = historial.some(item => 
        item.type === 'pokemon' && (item.name === queryNormalizado || item.id.toString() === queryNormalizado)
    );
    fetch(`https://pokeapi.co/api/v2/pokemon/${queryNormalizado}`)
        .then(response => {
            if (!response.ok) {
                throw new Error('Pokémon no encontrado.');
            }
            return response.json();
        })
        .then(data => {
            mostrarPokemon(data, isLocal);
            obtenerEvoluciones(data);
            agregarAHistorial({ type: 'pokemon', name: data.name, id: data.id, sprite: data.sprites ? data.sprites.front_default : '' });
        })
        .catch(error => {
            console.error('Error:', error);
            alert('No se encontró el Pokémon.');
        });
}

function buscarPorHabilidad(habilidad) {
    const queryNormalizado = typeof habilidad === 'string' ? habilidad.toLowerCase().replace(/\s+/g, '-') : habilidad;
    fetch(`https://pokeapi.co/api/v2/ability/${queryNormalizado}`)
        .then(response => {
            if (!response.ok) {
                throw new Error('Habilidad no encontrada.');
            }
            return response.json();
        })
        .then(data => {
            mostrarListaPokemonPorHabilidad(data);            // Añadir al historial
            agregarAHistorial({ type: 'habilidad', name: data.name });        })
        .catch(error => {
            console.error('Error:', error);
            alert('No se encontró la habilidad especificada. Ejemplos válidos: "chlorophyll", "overgrow", "1".');
        });
}

function mostrarListaPokemonPorHabilidad(dataHabilidad) {
    const contenedor = document.getElementById('resultado-container');
    const info = document.querySelector('.pokemon-info');
    
    if (contenedor && info) {
        const nombreHabilidad = dataHabilidad.name.toUpperCase().replace(/-/g, ' ');
        const total = dataHabilidad.pokemon.length;
        const pokemonList = dataHabilidad.pokemon.slice(0, 30);
        let listaHtml = pokemonList.map(p => {
            const nombreNormal = p.pokemon.name;
            const nombreDisplay = nombreNormal.toUpperCase().replace(/-/g, ' ');
            const urlParts = p.pokemon.url.split('/');
            const id = urlParts[urlParts.length - 2];
            const spriteUrl = `https://raw.githubusercontent.com/PokeAPI/sprites/master/sprites/pokemon/${id}.png`; 
            return `
                <div class="evo-ite" title="Ver a ${nombreDisplay}" onclick="buscarPokemon('${nombreNormal}')" style="margin-bottom: 10px;">
                    <img src="${spriteUrl}" alt="${nombreNormal}" onerror="this.src=''; this.alt='❓';">
                    <span>${nombreDisplay}</span>
                </div>
            `;
        }).join('');
        const mensajeLimite = total > 30 ? `<p style="text-align:center; color:#888; font-size: 0.8em; margin-top: 10px;">Mostrando 30 de ${total} Pokémon encontrados con esta habilidad.</p>` : '';
        const contenido = `
            <div class="poke-header">
                <h2>HABILIDAD <span class="poke-id">🌟</span></h2>
                <h3 style="color:#4CAF50; margin-top:5px;">${nombreHabilidad}</h3>
            </div>
            <div class="poke-evoluciones" style="border-top: none; margin-top: 0; padding-top: 0;">
                <p style="text-align:center; margin-bottom: 15px;">Pokémon que poseen esta habilidad:</p>
                <div class="evoluciones-lista">
                    ${listaHtml}
                </div>
                ${mensajeLimite}
            </div>
        `; 
        info.innerHTML = contenido;
        contenedor.style.display = 'block';
    }
}

function mostrarPokemon(pokemon, isLocal = false) {
    const contenedor = document.getElementById('resultado-container');
    const info = document.querySelector('.pokemon-info');
    
    if (contenedor && info) {
        info.style.position = 'relative';
        const sourceBadge = isLocal 
            ? `<div style="position: absolute; top: -15px; right: -15px; background-color: #bbfd6b; color: #000; padding: 5px 10px; font-size: 0.8rem; font-weight: 900; border-radius: 0; border: 3px solid #000; box-shadow: 2px 2px 0 0 #000; z-index: 10; transform: rotate(5deg);">📦 LOCAL</div>`
            : `<div style="position: absolute; top: -15px; right: -15px; background-color: aqua; color: #000; padding: 5px 10px; font-size: 0.8rem; font-weight: 900; border-radius: 0; border: 3px solid #000; box-shadow: 2px 2px 0 0 #000; z-index: 10; transform: rotate(5deg);">🌐 API</div>`;
        const idFormateado = '#' + pokemon.id.toString().padStart(4, '0');
        const sprite = pokemon.sprites && pokemon.sprites.front_default ? pokemon.sprites.front_default : '';
        const statsHtml = pokemon.stats.map(s => {
            const valor = s.base_stat;
            const porcentaje = Math.min((valor / 255) * 100, 100);
            return `
                <div class="stat-row">
                    <span class="stat-name">${s.stat.name.toUpperCase()}</span>
                    <span class="stat-value">${valor}</span>
                    <div class="stat-bar-bg">
                        <div class="stat-bar-fill" style="width: ${porcentaje}%"></div>
                    </div>
                </div>
            `;
        }).join('');
        const tiposHtml = pokemon.types.map(type => `<span class="badge tipo-${type.type.name}">${type.type.name.toUpperCase()}</span>`).join('');
        const habilidadesHtml = pokemon.abilities.map(ability => `<span class="badge habilidad">${ability.ability.name.toUpperCase()}</span>`).join('');
        const pokemonInfo = `
            ${sourceBadge}
            <div class="poke-header">
                <h2>${pokemon.name.toUpperCase()} <span class="poke-id">${idFormateado}</span></h2>
            </div>
            <img class="poke-sprite" src="${sprite}" alt="${pokemon.name}">
            <div class="poke-atributos">
                <div class="poke-seccion">
                    <h3>Tipo</h3>
                    <div class="badges-container">${tiposHtml}</div>
                </div>
                <div class="poke-seccion">
                    <h3>Habilidades</h3>
                    <div class="badges-container">${habilidadesHtml}</div>
                </div>
                <div class="poke-seccion-acciones" style="margin-top: 15px; text-align: center;">
                    <button class="btn-agregar-favorito" onclick="agregarFavorito('${pokemon.id}', '${pokemon.name}', '${sprite}')" style="background-color: #ff4d4d; color: white; border: none; padding: 10px 20px; border-radius: 5px; cursor: pointer; font-weight: bold;">
                        ❤️ Agregar a Favoritos
                    </button>
                </div>
            </div>
            <div class="poke-stats">
                <h3>Estadísticas Base</h3>
                ${statsHtml}
            </div>
            <div id="poke-evoluciones-container" class="poke-evoluciones">
                <h3>Cadena de Evolución</h3>
                <div class="evoluciones-lista" id="lista-evoluciones">
                    <p>Cargando evoluciones...</p>
                </div>
            </div>
        `;
        info.innerHTML = pokemonInfo;
        contenedor.style.display = 'block';
    }
}

async function obtenerEvoluciones(pokemonData) {
    try {
        const urlSpecies = pokemonData.species.url;
        const resSpecies = await fetch(urlSpecies);
        if (!resSpecies.ok) throw new Error('No se pudo encontrar datos de especie');
        const speciesData = await resSpecies.json();
        const evolutionUrl = speciesData.evolution_chain.url;
        const resEvolution = await fetch(evolutionUrl);
        if (!resEvolution.ok) throw new Error('No se pudo cargar la cadena de evolución');
        const evolutionData = await resEvolution.json();

        const arrEvoluciones = [];
        obtenerNombresEvolucion(evolutionData.chain, 0, arrEvoluciones);
        const fetchSprites = arrEvoluciones.map(async (evoMeta) => {
            let res = await fetch(`https://pokeapi.co/api/v2/pokemon/${evoMeta.name}`);
            if (!res.ok) {
                const resSp = await fetch(`https://pokeapi.co/api/v2/pokemon-species/${evoMeta.name}/`);
                if (resSp.ok) {
                    const spData = await resSp.json();
                    const defaultVar = spData.varieties.find(v => v.is_default);
                    if (defaultVar) {
                        res = await fetch(defaultVar.pokemon.url);
                    }
                }
            }
            const data = await res.json();
            return {
                name: data.name,
                sprite: data.sprites.front_default,
                id: data.id,
                level: evoMeta.level,
                isCurrent: data.id === pokemonData.id || data.name === evoMeta.name
            };
        });
        const evoData = await Promise.all(fetchSprites);
        mostrarEvoluciones(evoData);  
    } catch (error) {
        const evCont = document.getElementById('lista-evoluciones');
        if (evCont) evCont.innerHTML = `<p>Sin datos de evolución.</p>`;
        console.error(error);
    }
}

function obtenerNombresEvolucion(chainNode, level, resultList) {
    if (!chainNode) return;
    if (chainNode.species.name === 'lycanroc') {
        resultList.push({ name: 'lycanroc-midday', level });
        resultList.push({ name: 'lycanroc-midnight', level });
        resultList.push({ name: 'lycanroc-dusk', level });
    } else {
        resultList.push({ name: chainNode.species.name, level });
    }

    if (chainNode.evolves_to && chainNode.evolves_to.length > 0) {
        chainNode.evolves_to.forEach(siguienteEvo => {
             obtenerNombresEvolucion(siguienteEvo, level + 1, resultList);
        });
    }
}

function mostrarEvoluciones(evos) {
    const evCont = document.getElementById('lista-evoluciones');
    if (!evCont) return;

    const unicos = [...new Map(evos.map(v => [v.name, v])).values()];
    const evoHtml = unicos.map((evo, i) => {
        const isCurrentClass = evo.isCurrent ? 'evo-actual' : '';
        const displayName = evo.name.toUpperCase().replace(/-/g, ' ');
        const div = `
            <div class="evo-ite ${isCurrentClass}" title="Ver a ${displayName}" onclick="buscarPokemon('${evo.name}')">
                <img src="${evo.sprite}" alt="${evo.name}">
                <span>${displayName}</span>
            </div>
        `;
        let arrow = '';
        if (i < unicos.length - 1) {
            const nextEvo = unicos[i + 1];
            if (nextEvo.level > evo.level) {
                arrow = `<div class="evo-flecha">➡️</div>`;
            }
        }
        return div + arrow;
    }).join('');
    evCont.innerHTML = evoHtml;
}

// ---- Favoritos ---

function agregarFavorito(id, nombre, sprite) {
    let favoritos = JSON.parse(localStorage.getItem('pokemonFavoritos') || '[]');
    if (!favoritos.find(p => p.id === id)) {
        favoritos.push({ id, nombre, sprite });
        localStorage.setItem('pokemonFavoritos', JSON.stringify(favoritos));
        alert(nombre.toUpperCase() + ' ha sido agregado a favoritos ❤️');
    } else {
        alert(nombre.toUpperCase() + ' ya está en tus favoritos.');
    }
}

function mostrarFavoritos() {
    const contenedor = document.getElementById('resultado-container');
    const info = document.querySelector('.pokemon-info');
    
    if (contenedor && info) {
        let favoritos = JSON.parse(localStorage.getItem('pokemonFavoritos') || '[]');
        let listaHtml = favoritos.map(p => {
            const nombreDisplay = p.nombre.toUpperCase().replace(/-/g, ' ');
            const idDisplay = '#' + p.id.toString().padStart(4, '0');
            return `
                <div class="evo-ite" title="Ver a ${nombreDisplay}" onclick="buscarPokemon('${p.nombre}')" style="margin-bottom: 10px; cursor: pointer; display: flex; flex-direction: row; align-items: center; justify-content: space-between; width: 100%; max-width: 350px; padding: 5px 15px; border: 1px solid #eee; border-radius: 10px; background-color: #fafafa;">
                    <div style="display: flex; align-items: center; gap: 15px;">
                        <img src="${p.sprite}" alt="${p.nombre}" onerror="this.src=''; this.alt='❓';" style="width: 60px; height: 60px;">
                        <span style="font-weight: bold; font-size: 1.1em;">${nombreDisplay} <span style="color: #888; font-size: 0.8em; margin-left: 5px;">${idDisplay}</span></span>
                    </div>
                    <button onclick="event.stopPropagation(); eliminarFavorito('${p.id}')" title="Quitar de favoritos" style="background: none; border: none; cursor: pointer; font-size: 1.5em; transition: transform 0.2s;" onmouseover="this.style.transform='scale(1.2)'" onmouseout="this.style.transform='scale(1)'">
                        💔
                    </button>
                </div>
            `;
        }).join('');

        let btnBorrarTodos = '';
        if (favoritos.length === 0) {
            listaHtml = '<p style="text-align: center; color: #888;">No tienes ningún Pokémon en favoritos aún.</p>';
        } else {
            btnBorrarTodos = `
                <div style="text-align: center; margin-top: 25px; padding-top: 15px; border-top: 1px solid #eee;">
                    <button onclick="borrarTodosFavoritos()" style="background-color: #ff4d4d; color: white; border: none; padding: 10px 20px; border-radius: 5px; cursor: pointer; font-weight: bold;">
                        🗑️ Borrar lista de favoritos
                    </button>
                </div>
            `;
        }
        const contenido = `
            <div class="poke-header">
                <h2>TUS FAVORITOS ❤️</h2>
            </div>    
            <div class="poke-evoluciones" style="border-top: none; margin-top: 0; padding-top: 0;">
                <div class="evoluciones-lista" style="display: flex; flex-direction: column; align-items: center; gap: 10px;">
                    ${listaHtml}
                </div>
                ${btnBorrarTodos}
            </div>
        `;  
        info.innerHTML = contenido;
        contenedor.style.display = 'block';
    }
}

function eliminarFavorito(id) {
    let favoritos = JSON.parse(localStorage.getItem('pokemonFavoritos') || '[]');
    favoritos = favoritos.filter(p => p.id !== id);
    localStorage.setItem('pokemonFavoritos', JSON.stringify(favoritos));
    mostrarFavoritos(); 
}

function borrarTodosFavoritos() {
    if (confirm('¿Estás seguro de que deseas borrar toda tu lista de favoritos? Esta acción no se puede deshacer.')) {
        localStorage.removeItem('pokemonFavoritos');
        mostrarFavoritos();
    }
}




// ---- Historial ---

function agregarAHistorial(item) {
    let historial = JSON.parse(localStorage.getItem('pokemonHistorial') || '[]');
    historial = historial.filter(i => !(i.type === item.type && i.name === item.name));
    historial.unshift(item); 

    if (historial.length > 50) historial.pop();
    localStorage.setItem('pokemonHistorial', JSON.stringify(historial));
}

function mostrarHistorial() {
    const contenedor = document.getElementById('resultado-container');
    const info = document.querySelector('.pokemon-info');
    
    if (contenedor && info) {
        let historial = JSON.parse(localStorage.getItem('pokemonHistorial') || '[]');   
        let listaHtml = historial.map((item, index) => {
            const nombreDisplay = item.name.toUpperCase().replace(/-/g, ' ');
            if (item.type === 'pokemon') {
                const idDisplay = '#' + item.id.toString().padStart(4, '0');
                return `
                    <div class="evo-ite" title="Ver a ${nombreDisplay}" onclick="buscarPokemon('${item.name}')" style="margin-bottom: 10px; cursor: pointer; display: flex; flex-direction: row; align-items: center; justify-content: space-between; width: 100%; max-width: 350px; padding: 5px 15px; border: 1px solid #eee; border-radius: 10px; background-color: #fafafa;">
                        <div style="display: flex; align-items: center; gap: 15px;">
                            <img src="${item.sprite}" alt="${item.name}" onerror="this.src=''; this.alt='👾';" style="width: 60px; height: 60px;">
                            <span style="font-weight: bold; font-size: 1.1em;">${nombreDisplay} <span style="color: #888; font-size: 0.8em; margin-left: 5px;">${idDisplay}</span></span>
                        </div>
                        <button onclick="event.stopPropagation(); eliminarHistorial(${index})" title="Quitar del historial" style="background: none; border: none; cursor: pointer; font-size: 1.5em; transition: transform 0.2s;" onmouseover="this.style.transform='scale(1.2)'" onmouseout="this.style.transform='scale(1)'">
                            ❌
                        </button>
                    </div>
                `;
            } else {
                return `
                    <div class="evo-ite" title="Ver habilidad ${nombreDisplay}" onclick="buscarPorHabilidad('${item.name}')" style="margin-bottom: 10px; cursor: pointer; display: flex; flex-direction: row; align-items: center; justify-content: space-between; width: 100%; max-width: 350px; padding: 5px 15px; border: 1px solid #eee; border-radius: 10px; background-color: #eef7ff;">
                        <div style="display: flex; align-items: center; gap: 15px;">
                            <div style="width: 60px; height: 60px; display: flex; align-items: center; justify-content: center; font-size: 2em;">🌟</div>
                            <span style="font-weight: bold; font-size: 1.1em; color: #0056b3;">HAB: ${nombreDisplay}</span>
                        </div>
                        <button onclick="event.stopPropagation(); eliminarHistorial(${index})" title="Quitar del historial" style="background: none; border: none; cursor: pointer; font-size: 1.5em; transition: transform 0.2s;" onmouseover="this.style.transform='scale(1.2)'" onmouseout="this.style.transform='scale(1)'">
                            ❌
                        </button>
                    </div>
                `;
            }
        }).join('');
        let btnBorrarTodos = '';
        if (historial.length === 0) {
            listaHtml = '<p style="text-align: center; color: #888;">El historial de búsqueda está vacío.</p>';
        } else {
            btnBorrarTodos = `
                <div style="text-align: center; margin-top: 25px; padding-top: 15px; border-top: 1px solid #eee;">
                    <button onclick="borrarTodoHistorial()" style="background-color: #ff4d4d; color: white; border: none; padding: 10px 20px; border-radius: 5px; cursor: pointer; font-weight: bold;">
                        🗑️ Borrar todo el historial
                    </button>
                </div>
            `;
        }
        const contenido = `
            <div class="poke-header">
                <h2>📜 HISTORIAL DE BÚSQUEDAS</h2>
            </div>   
            <div class="poke-evoluciones" style="border-top: none; margin-top: 0; padding-top: 0;">
                <div class="evoluciones-lista" style="display: flex; flex-direction: column; align-items: center; gap: 10px;">
                    ${listaHtml}
                </div>
                ${btnBorrarTodos}
            </div>
        `;   
        info.innerHTML = contenido;
        contenedor.style.display = 'block';
    }
}

function eliminarHistorial(index) {
    let historial = JSON.parse(localStorage.getItem('pokemonHistorial') || '[]');
    historial.splice(index, 1);
    localStorage.setItem('pokemonHistorial', JSON.stringify(historial));
    mostrarHistorial(); 
}

function borrarTodoHistorial() {
    if (confirm('¿Estás seguro de que deseas borrar todo tu historial de búsqueda? Esta acción no se puede deshacer.')) {
        localStorage.removeItem('pokemonHistorial');
        mostrarHistorial(); 
    }
}




// ---- VS Mode ---
function mostrarVistaVS() {
    const contenedor = document.getElementById('resultado-container');
    const info = document.querySelector('.pokemon-info');
    
    if (contenedor && info) {
        const contenido = `
            <div class="poke-header" style="border-bottom: 5px solid #000;">
                <h2>⚔️ MODO VERSUS ⚔️</h2>
            </div>
            
            <div style="display: flex; flex-direction: column; gap: 20px; padding: 20px 0;">
                <p style="text-align: center; font-weight: bold; color: #333; margin: 0;">¡Elige a tus combatientes!</p>
                <div style="display: flex; justify-content: space-around; align-items: center; flex-wrap: wrap; gap: 15px;">
                    <div style="text-align: center; flex: 1; min-width: 150px;">
                        <input type="text" id="vs-pokemon-1" class="input-text" placeholder="POKÉMON 1" style="width: 100%; text-align: center; border-radius: 0;">
                    </div>
                    <div style="font-size: 2.5em; font-weight: 900; color: #fff; background-color: #ff4d4d; border: 5px solid #000; border-radius: 50%; width: 60px; height: 60px; display: flex; align-items: center; justify-content: center; box-shadow: #000 4px 4px 0px 0px; text-shadow: 2px 2px 0 #000;">
                        VS
                    </div>
                    <div style="text-align: center; flex: 1; min-width: 150px;">
                        <input type="text" id="vs-pokemon-2" class="input-text" placeholder="POKÉMON 2" style="width: 100%; text-align: center; border-radius: 0;">
                    </div>
                </div>
                <div style="text-align: center; margin-top: 15px;">
                    <button onclick="realizarVS()" class="btn-buscar" style="width: 200px; height: 60px; font-size: 1.2rem; background-color: #bbfd6b; color: #000; border: 5px solid #000; box-shadow: #000 5px 5px 0px 0px; text-shadow: none;">
                        ¡COMPARAR!
                    </button>
                    <div id="vs-error" style="color: red; margin-top: 15px; font-weight: bold; min-height: 20px;"></div>
                </div>
            </div>
            <div id="vs-resultado" style="width: 100%;"></div>
        `;
        info.innerHTML = contenido;
        contenedor.style.display = 'block';
    }
}

async function realizarVS() {
    const input1 = document.getElementById('vs-pokemon-1').value.trim().toLowerCase();
    const input2 = document.getElementById('vs-pokemon-2').value.trim().toLowerCase();
    const errorDiv = document.getElementById('vs-error');
    const resultadoDiv = document.getElementById('vs-resultado');
    
    if (!input1 || !input2) {
        errorDiv.textContent = 'Por favor, ingresa dos Pokémon para comparar.';
        return;
    }
    errorDiv.textContent = 'Buscando y calculando...';
    resultadoDiv.innerHTML = '';
    try {
        const [res1, res2] = await Promise.all([
            fetch(`https://pokeapi.co/api/v2/pokemon/${input1}`),
            fetch(`https://pokeapi.co/api/v2/pokemon/${input2}`)
        ]);
        if (!res1.ok || !res2.ok) {
            throw new Error('Uno o ambos Pokémon no fueron encontrados.');
        }
        const poke1 = await res1.json();
        const poke2 = await res2.json();
        const statsP1 = poke1.stats.reduce((acc, stat) => acc + stat.base_stat, 0);
        const statsP2 = poke2.stats.reduce((acc, stat) => acc + stat.base_stat, 0);
        const typeData = await obtenerRelacionesDeTipos(poke1.types, poke2.types);
        
        mostrarResultadoVS(poke1, poke2, statsP1, statsP2, typeData);
        errorDiv.textContent = '';   
    } catch (err) {
        errorDiv.textContent = err.message;
    }
}

async function obtenerRelacionesDeTipos(types1, types2) {
    const calcMultiplier = async (attackTypeUrl, defTypesNames) => {
        let mult = 1;
        const res = await fetch(attackTypeUrl);
        const data = await res.json();
        const damageRelations = data.damage_relations;
        
        defTypesNames.forEach(defType => {
            if (damageRelations.double_damage_to.some(t => t.name === defType)) mult *= 2;
            if (damageRelations.half_damage_to.some(t => t.name === defType)) mult *= 0.5;
            if (damageRelations.no_damage_to.some(t => t.name === defType)) mult *= 0;
        });
        return mult;
    };
    
    const defNames1 = types1.map(t => t.type.name);
    const defNames2 = types2.map(t => t.type.name);
    let bestMultP1 = 0;
    for (const t1 of types1) {
        const mult = await calcMultiplier(t1.type.url, defNames2);
        if (mult > bestMultP1) bestMultP1 = mult;
    }
    let bestMultP2 = 0;
    for (const t2 of types2) {
        const mult = await calcMultiplier(t2.type.url, defNames1);
        if (mult > bestMultP2) bestMultP2 = mult;
    }
    return { p1M: bestMultP1, p2M: bestMultP2 };
}

function mostrarResultadoVS(poke1, poke2, statsP1, statsP2, typeData) {
    const resDiv = document.getElementById('vs-resultado');
    if (!resDiv) return;
    

    // Ganador por stats
    let ganadorStats = '<span style="color:#555;">Empate</span>';
    if (statsP1 > statsP2) ganadorStats = `<span style="color:#4CAF50;">🏆 ${poke1.name.toUpperCase()}</span>`;
    else if (statsP2 > statsP1) ganadorStats = `<span style="color:#4CAF50;">🏆 ${poke2.name.toUpperCase()}</span>`;
    
    const getTypeMultText = (mult) => {
        if (mult > 1) return `<div style="background-color:#bbfd6b; border: 3px solid #000; padding: 5px; font-weight: 900; margin-top:5px; box-shadow: 2px 2px 0 #000;">Súper efectivo (${mult}x)</div>`;
        if (mult === 1) return `<div style="background-color:#eee; border: 3px solid #000; padding: 5px; font-weight: 900; margin-top:5px; box-shadow: 2px 2px 0 #000;">Daño normal (1x)</div>`;
        if (mult > 0) return `<div style="background-color:#ffd700; border: 3px solid #000; padding: 5px; font-weight: 900; margin-top:5px; box-shadow: 2px 2px 0 #000;">Poco efectivo (${mult}x)</div>`;
        return `<div style="background-color:#fa3e45; color:#fff; border: 3px solid #000; padding: 5px; font-weight: 900; margin-top:5px; box-shadow: 2px 2px 0 #000;">Sin efecto (0x)</div>`;
    };

    const getStatColor = (val1, val2) => {
        if (val1 > val2) return 'color: #4CAF50; font-weight: 900; font-size: 1.2em;';
        if (val1 < val2) return 'color: #fa3e45; text-decoration: line-through; opacity: 0.7;';
        return 'color: #555;';
    };

    let statComparisonHtml = poke1.stats.map((s, index) => {
        const val1 = s.base_stat;
        const val2 = poke2.stats[index].base_stat;
        const statName = s.stat.name.toUpperCase();
        return `
            <div style="display: flex; justify-content: space-between; align-items: center; border-bottom: 2px dashed #ccc; padding: 8px 0;">
                <span style="flex: 1; text-align: center; ${getStatColor(val1, val2)}">${val1}</span>
                <span style="flex: 1; text-align: center; font-weight: 900; font-size: 0.85em; background: #eee; border: 2px solid #000; padding: 3px; border-radius: 5px;">${statName}</span>
                <span style="flex: 1; text-align: center; ${getStatColor(val2, val1)}">${val2}</span>
            </div>
        `;
    }).join('');

    const html = `
        <div style="border-top: 5px solid #000; margin-top: 20px; padding-top: 20px;">
            <div style="display: flex; justify-content: space-around; text-align: center; margin-bottom: 20px; align-items: flex-start;">
                
                <!-- POKEMON 1 -->
                <div style="flex: 1; display: flex; flex-direction: column; align-items: center; background: #fff; border: 5px solid #000; box-shadow: -5px 5px 0 0 #000; padding: 15px; margin-right: 10px; position: relative;">
                    <span style="position: absolute; top: -15px; left: -15px; background: #000; color: #fff; padding: 5px 10px; font-weight: bold; border: 3px solid #fff; box-shadow: 2px 2px 0 0 #000;">P1</span>
                    <img src="${poke1.sprites.front_default || ''}" style="width: 140px; height: 140px; background: #f0f0f0; border-radius: 50%; border: 5px solid #000; margin-bottom: 10px; box-shadow: inset 0 0 10px rgba(0,0,0,0.5);">
                    <h3 style="margin: 0 0 10px; font-size: 1.2rem; font-weight: 900;">${poke1.name.toUpperCase()}</h3>
                    <div style="margin-bottom: 10px; display: flex; gap: 5px; flex-wrap: wrap; justify-content: center;">
                        ${poke1.types.map(t => `<span class="badge tipo-${t.type.name}">${t.type.name.toUpperCase()}</span>`).join('')}
                    </div>
                    <div style="font-weight: 900; font-size: 1.1rem; border-top: 2px solid #000; padding-top: 10px; width: 100%;">
                        Stats: ${statsP1}
                    </div>
                    <div style="margin-top: 15px; font-size: 0.85rem; width: 100%;">
                        <b>Ataque a P2</b><br>
                        ${getTypeMultText(typeData.p1M)}
                    </div>
                </div>
                
                <!-- POKEMON 2 -->
                <div style="flex: 1; display: flex; flex-direction: column; align-items: center; background: #fff; border: 5px solid #000; box-shadow: 5px 5px 0 0 #000; padding: 15px; margin-left: 10px; position: relative;">
                    <span style="position: absolute; top: -15px; right: -15px; background: #000; color: #fff; padding: 5px 10px; font-weight: bold; border: 3px solid #fff; box-shadow: -2px 2px 0 0 #000;">P2</span>
                    <img src="${poke2.sprites.front_default || ''}" style="width: 140px; height: 140px; background: #f0f0f0; border-radius: 50%; border: 5px solid #000; margin-bottom: 10px; box-shadow: inset 0 0 10px rgba(0,0,0,0.5);">
                    <h3 style="margin: 0 0 10px; font-size: 1.2rem; font-weight: 900;">${poke2.name.toUpperCase()}</h3>
                    <div style="margin-bottom: 10px; display: flex; gap: 5px; flex-wrap: wrap; justify-content: center;">
                        ${poke2.types.map(t => `<span class="badge tipo-${t.type.name}">${t.type.name.toUpperCase()}</span>`).join('')}
                    </div>
                    <div style="font-weight: 900; font-size: 1.1rem; border-top: 2px solid #000; padding-top: 10px; width: 100%;">
                        Stats: ${statsP2}
                    </div>
                    <div style="margin-top: 15px; font-size: 0.85rem; width: 100%;">
                        <b>Ataque a P1</b><br>
                        ${getTypeMultText(typeData.p2M)}
                    </div>
                </div>

            </div>
            
            <div style="background: #fff; border: 5px solid #000; box-shadow: 5px 5px 0 0 #000; padding: 20px; margin-top: 30px;">
                <div style="text-align: center; margin-bottom: 20px;">
                    <h3 style="margin: 0; font-weight: 900; background: aqua; display: inline-block; padding: 15px 30px; border: 3px solid #000; transform: rotate(-2deg);">TABLA DE ESTADÍSTICAS</h3>
                </div>
                <div style="display: flex; justify-content: space-between; border-bottom: 5px solid #000; padding-bottom: 10px; margin-bottom: 10px; font-weight: 900; font-size: 1.1rem;">
                    <span style="flex: 1; text-align: center;">P1</span>
                    <span style="flex: 1; text-align: center;">V.S</span>
                    <span style="flex: 1; text-align: center;">P2</span>
                </div>
                ${statComparisonHtml}
                <div style="text-align: center; margin-top: 20px; font-weight: 900; font-size: 1.5rem; background: #000; color: #fff; padding: 10px; border: 2px dashed #fff;">
                    👑 MAYOR PODER BASE: ${ganadorStats} 👑
                </div>
            </div>
        </div>
    `;
    resDiv.innerHTML = html;
}


